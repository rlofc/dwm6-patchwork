/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[]			= "Terminus:size=9:antialias=true:hinting=true";
#define NUMCOLORS 4
static const char colors[NUMCOLORS][ColLast][9] = {
	/* border	foreground	background */
	/* gaia2 */
	{ "#666666", "#000000", "#333333" }, // 1 = normal
	{ "#FDBE45", "#FFA905", "#333333" }, // 2 = selected
	{ "#F54844", "#F54844", "#333333" }, // 3 = urgent
	{ "#93C724", "#F9F9F9", "#333333" }, // 4 = occupied
};
static const unsigned int systrayspacing	= 1;	// Systray spacing
static const unsigned int borderpx			= 2;	// Border pixel of windows
static const unsigned int gappx				= 3;	// Gap pixel between windows
static const unsigned int snap				= 2;	// Snap pixel
//static const float opacity				= 0.75;	// Opacity of the statusbar (max 0.75)
static const Bool showbar					= True;	// False means no bar
static const Bool showsystray				= True;	// False means no systray
static const Bool topbar					= True;	// False means bottom bar

/* layout(s) */
static const float mfact		= 0.63;		// factor of master area size [0.05..0.95]
static const int nmaster 		= 1;		// number of clients in master area
static const Bool resizehints	= False;	// True means respect size hints in tiled resizals

static const Layout layouts[] = {
	/* symbol	gaps	arrange */
	{ "   T",	True,	tile	},
	{ "   B",	True,	bstack	},
	{ "   M",	False,	monocle	},
	{ "   F",	False,	NULL	},
};

/* tagging */
static const Tag tags[] = {
	/* name		layout       mfact		nmaster */
	{ "1",	&layouts[0], -1,		-1 },
	{ "2",	&layouts[0], -1,		-1 },
	{ "3",	&layouts[0], -1,		-1 },
	{ "4",	&layouts[0], -1,		-1 },
	{ "5",	&layouts[0], -1,		-1 },
	{ "6",	&layouts[0], -1,		-1 },
	{ "7",	&layouts[0], -1,		-1 },
	{ "8",	&layouts[0], -1,		-1 },
	{ "9",	&layouts[0], -1,		-1 },
};

static const Rule rules[] = {
	/*WM_CLASS		WM_CLASS	WM_NAME
	  class			instance	title				tags mask	isfloating	monitor */
	{ "Chromium",	NULL,		NULL,				1 << 8,			False,		-1 },
	{ NULL,			NULL,		"Jagex Ltd.",		1 << 1,		True,		-1 },
	{ NULL,			NULL,		"RuneScape",		1 << 1,		False,		-1 },
	{ "Skype",		NULL,		NULL,				1 << 1,		False,		-1 },
	{ "Skype",		NULL,		"Call with Aggi~",	1 << 1,		True,		-1 },
	{ NULL,			"ncmpcpp",	NULL,				1 << 3,		False,		-1 },
	{ "MPlayer",	NULL,		NULL,				1 << 3,		True,		-1 },
	{ "Gimp",		NULL,		NULL,				1 << 3,		False,		-1 },
	{ "Evince",		NULL,		NULL, 				1 << 4,		False,		-1 },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MONKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,			KEY, view, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,	KEY, tag,  {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenu[]		= { "dmenu_run", "-p", "RUN >>>", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *term[]		= { "urxvt", NULL };
static const char *browser[]	= { "chromium", NULL };
static const char *files[]		= { "ranger", NULL };
static const char *music[]		= { "urxvtc", "-name", "ncmpcpp", "-e", "ncmpcpp", NULL };
static const char *skype[]		= { "skype", NULL };
static const char *scrot[]		= { "scrot", NULL };
static const char *kill[]		= { "xkill", NULL };
static const char *lock[]		= { "slock", NULL };
static const char *halt[]		= { "dmenu_shutdown", NULL };
static const char *volup[]		= { "amixer", "-q", "sset", "Master", "5%+", "unmute", NULL };
static const char *voldown[]	= { "amixer", "-q", "sset", "Master", "5%-", "unmute", NULL };
static const char *volmute[]	= { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *mpdplay[]	= { "ncmpcpp", "toggle", NULL };
static const char *mpdnext[]	= { "ncmpcpp", "next", NULL };
static const char *mpdprev[]	= { "ncmpcpp", "prev", NULL };
static const char *mpdstop[]	= { "ncmpcpp", "stop", NULL };

static Key keys[] = {
	/* modifier					key				 			function		argument */
	{ MODKEY,					XK_p,						spawn,			{.v = dmenu } },
	{ MODKEY,					XK_x,						spawn,			{.v = kill } },
	{ MODKEY,					XK_l,						spawn,			{.v = lock } },
	{ MODKEY,					XK_Escape,					spawn,			{.v = halt } },
	{ MODKEY,					XK_Return,						spawn,			{.v = term } },
	{ 0,						XK_Print,					spawn,			{.v = scrot } },
	{ 0,						XF86XK_AudioRaiseVolume,	spawn,			{.v = volup } },
	{ 0,						XF86XK_AudioLowerVolume,	spawn,			{.v = voldown } },
	{ 0,						XF86XK_AudioMute,			spawn,			{.v = volmute } },
	{ 0,						XF86XK_AudioPlay,			spawn,			{.v = mpdplay } },
	{ 0,						XF86XK_AudioNext,			spawn,			{.v = mpdnext } },
	{ 0,						XF86XK_AudioPrev,			spawn,			{.v = mpdprev } },
	{ 0,						XF86XK_AudioStop,			spawn,			{.v = mpdstop } },
	{ MODKEY|ControlMask,		XK_b,						togglebar,		{0} },
	{ MODKEY|ControlMask,		XK_q,						quit,			{0} },
	{ MODKEY,					XK_Right,					focusstack,		{.i = +1 } },
	{ MODKEY,					XK_Left,					focusstack,		{.i = -1 } },
	{ MODKEY,					XK_Return,					zoom,			{0} },
	{ MODKEY,					XK_Tab,						view,			{0} },
	{ MODKEY,					XK_q,						killclient,		{0} },
	{ MODKEY,					XK_bracketleft,				setmfact,		{.f = -0.05} },
	{ MODKEY,					XK_bracketright,			setmfact,		{.f = +0.05} },
	{ MODKEY,					XK_equal,					incnmaster,		{.i = +1 } },
	{ MODKEY,					XK_minus,					incnmaster,		{.i = -1 } },
	{ MODKEY,					XK_space,					setlayout,		{0} },
	{ MODKEY|ShiftMask,			XK_f,						togglefloating,	{0} },
	{ MODKEY,					XK_t,						setlayout,		{.v = &layouts[0] } },
	{ MODKEY,					XK_b,						setlayout,		{.v = &layouts[1] } },
	{ MODKEY,					XK_m,						setlayout,		{.v = &layouts[2] } },
	{ MODKEY,					XK_f,						setlayout,		{.v = &layouts[3] } },
	TAGKEYS(					XK_1,						0)
	TAGKEYS(					XK_2,						1)
	TAGKEYS(					XK_3,						2)
	TAGKEYS(					XK_4,						3)
	TAGKEYS(					XK_5,						4)
	TAGKEYS(					XK_6,						5)
	TAGKEYS(					XK_7,						6)
	TAGKEYS(					XK_8,						7)
	TAGKEYS(					XK_9,						8)
	{ MODKEY,					XK_o,						view,			{.ui = ~0 } },
	{ MODKEY|ShiftMask,			XK_a,						tag,			{.ui = ~0 } },
	{ MONKEY,					XK_Left,					focusmon,		{.i = -1 } },
	{ MONKEY,					XK_Right,					focusmon,		{.i = +1 } },
	{ MONKEY|ShiftMask,			XK_Left,					tagmon,			{.i = -1 } },
	{ MONKEY|ShiftMask,			XK_Right,					tagmon,			{.i = +1 } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click			event mask	button		function		argument */
	{ ClkLtSymbol,		0,			Button1,	setlayout,		{0} },
	{ ClkLtSymbol,		0,			Button3,	setlayout,		{.v = &layouts[4]} },
	{ ClkStatusText,	0,			Button2,	spawn,			{.v = term } },
	{ ClkClientWin,		MODKEY,		Button1,	movemouse,		{0} },
	{ ClkClientWin,		MODKEY,		Button2,	togglefloating,	{0} },
	{ ClkClientWin,		MODKEY,		Button3,	resizemouse,	{0} },
	{ ClkTagBar,		0,			Button1,	view,			{0} },
	{ ClkTagBar,		MODKEY,		Button1,	tag,			{0} },
};
