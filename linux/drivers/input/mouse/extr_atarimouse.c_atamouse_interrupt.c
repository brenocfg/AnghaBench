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

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  atamouse_dev ; 
 int atari_mouse_buttons ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atamouse_interrupt(char *buf)
{
	int buttons, dx, dy;

	buttons = (buf[0] & 1) | ((buf[0] & 2) << 1);
#ifdef FIXED_ATARI_JOYSTICK
	buttons |= atari_mouse_buttons & 2;
	atari_mouse_buttons = buttons;
#endif

	/* only relative events get here */
	dx = buf[1];
	dy = buf[2];

	input_report_rel(atamouse_dev, REL_X, dx);
	input_report_rel(atamouse_dev, REL_Y, dy);

	input_report_key(atamouse_dev, BTN_LEFT,   buttons & 0x4);
	input_report_key(atamouse_dev, BTN_MIDDLE, buttons & 0x2);
	input_report_key(atamouse_dev, BTN_RIGHT,  buttons & 0x1);

	input_sync(atamouse_dev);

	return;
}