#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ps2pp_info {int member_0; int member_2; unsigned char model; int /*<<< orphan*/  const member_1; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ps2pp_info const*) ; 
#define  PS2PP_EXTRA_BTN 137 
#define  PS2PP_HWHEEL 136 
#define  PS2PP_KIND_MX 135 
#define  PS2PP_KIND_TP3 134 
#define  PS2PP_KIND_TRACKMAN 133 
#define  PS2PP_KIND_WHEEL 132 
#define  PS2PP_NAV_BTN 131 
#define  PS2PP_SIDE_BTN 130 
#define  PS2PP_TASK_BTN 129 
#define  PS2PP_WHEEL 128 

__attribute__((used)) static const struct ps2pp_info *get_model_info(unsigned char model)
{
	static const struct ps2pp_info ps2pp_list[] = {
		{  1,	0,			0 },	/* Simple 2-button mouse */
		{ 12,	0,			PS2PP_SIDE_BTN},
		{ 13,	0,			0 },
		{ 15,	PS2PP_KIND_MX,					/* MX1000 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN | PS2PP_HWHEEL },
		{ 40,	0,			PS2PP_SIDE_BTN },
		{ 41,	0,			PS2PP_SIDE_BTN },
		{ 42,	0,			PS2PP_SIDE_BTN },
		{ 43,	0,			PS2PP_SIDE_BTN },
		{ 50,	0,			0 },
		{ 51,	0,			0 },
		{ 52,	PS2PP_KIND_WHEEL,	PS2PP_SIDE_BTN | PS2PP_WHEEL },
		{ 53,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 56,	PS2PP_KIND_WHEEL,	PS2PP_SIDE_BTN | PS2PP_WHEEL }, /* Cordless MouseMan Wheel */
		{ 61,	PS2PP_KIND_MX,					/* MX700 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN },
		{ 66,	PS2PP_KIND_MX,					/* MX3100 receiver */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN | PS2PP_HWHEEL },
		{ 72,	PS2PP_KIND_TRACKMAN,	0 },			/* T-CH11: TrackMan Marble */
		{ 73,	PS2PP_KIND_TRACKMAN,	PS2PP_SIDE_BTN },	/* TrackMan FX */
		{ 75,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 76,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 79,	PS2PP_KIND_TRACKMAN,	PS2PP_WHEEL },		/* TrackMan with wheel */
		{ 80,	PS2PP_KIND_WHEEL,	PS2PP_SIDE_BTN | PS2PP_WHEEL },
		{ 81,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 83,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 85,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 86,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 87,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 88,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 96,	0,			0 },
		{ 97,	PS2PP_KIND_TP3,		PS2PP_WHEEL | PS2PP_HWHEEL },
		{ 99,	PS2PP_KIND_WHEEL,	PS2PP_WHEEL },
		{ 100,	PS2PP_KIND_MX,					/* MX510 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN },
		{ 111,  PS2PP_KIND_MX,	PS2PP_WHEEL | PS2PP_SIDE_BTN },	/* MX300 reports task button as side */
		{ 112,	PS2PP_KIND_MX,					/* MX500 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTRA_BTN | PS2PP_NAV_BTN },
		{ 114,	PS2PP_KIND_MX,					/* MX310 */
				PS2PP_WHEEL | PS2PP_SIDE_BTN |
				PS2PP_TASK_BTN | PS2PP_EXTRA_BTN }
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(ps2pp_list); i++)
		if (model == ps2pp_list[i].model)
			return &ps2pp_list[i];

	return NULL;
}