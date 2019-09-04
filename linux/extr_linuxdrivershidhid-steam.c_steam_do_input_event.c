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
typedef  int u8 ;
struct steam_device {int dummy; } ;
struct input_dev {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_HAT2X ; 
 int /*<<< orphan*/  ABS_HAT2Y ; 
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int BIT (int) ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  BTN_DPAD_DOWN ; 
 int /*<<< orphan*/  BTN_DPAD_LEFT ; 
 int /*<<< orphan*/  BTN_DPAD_RIGHT ; 
 int /*<<< orphan*/  BTN_DPAD_UP ; 
 int /*<<< orphan*/  BTN_GEAR_DOWN ; 
 int /*<<< orphan*/  BTN_GEAR_UP ; 
 int /*<<< orphan*/  BTN_MODE ; 
 int /*<<< orphan*/  BTN_SELECT ; 
 int /*<<< orphan*/  BTN_START ; 
 int /*<<< orphan*/  BTN_THUMB ; 
 int /*<<< orphan*/  BTN_THUMB2 ; 
 int /*<<< orphan*/  BTN_THUMBL ; 
 int /*<<< orphan*/  BTN_THUMBR ; 
 int /*<<< orphan*/  BTN_TL ; 
 int /*<<< orphan*/  BTN_TL2 ; 
 int /*<<< orphan*/  BTN_TR ; 
 int /*<<< orphan*/  BTN_TR2 ; 
 int /*<<< orphan*/  BTN_X ; 
 int /*<<< orphan*/  BTN_Y ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int steam_le16 (int*) ; 

__attribute__((used)) static void steam_do_input_event(struct steam_device *steam,
		struct input_dev *input, u8 *data)
{
	/* 24 bits of buttons */
	u8 b8, b9, b10;
	s16 x, y;
	bool lpad_touched, lpad_and_joy;

	b8 = data[8];
	b9 = data[9];
	b10 = data[10];

	input_report_abs(input, ABS_HAT2Y, data[11]);
	input_report_abs(input, ABS_HAT2X, data[12]);

	/*
	 * These two bits tells how to interpret the values X and Y.
	 * lpad_and_joy tells that the joystick and the lpad are used at the
	 * same time.
	 * lpad_touched tells whether X/Y are to be read as lpad coord or
	 * joystick values.
	 * (lpad_touched || lpad_and_joy) tells if the lpad is really touched.
	 */
	lpad_touched = b10 & BIT(3);
	lpad_and_joy = b10 & BIT(7);
	x = steam_le16(data + 16);
	y = -steam_le16(data + 18);

	input_report_abs(input, lpad_touched ? ABS_HAT0X : ABS_X, x);
	input_report_abs(input, lpad_touched ? ABS_HAT0Y : ABS_Y, y);
	/* Check if joystick is centered */
	if (lpad_touched && !lpad_and_joy) {
		input_report_abs(input, ABS_X, 0);
		input_report_abs(input, ABS_Y, 0);
	}
	/* Check if lpad is untouched */
	if (!(lpad_touched || lpad_and_joy)) {
		input_report_abs(input, ABS_HAT0X, 0);
		input_report_abs(input, ABS_HAT0Y, 0);
	}

	input_report_abs(input, ABS_RX, steam_le16(data + 20));
	input_report_abs(input, ABS_RY, -steam_le16(data + 22));

	input_event(input, EV_KEY, BTN_TR2, !!(b8 & BIT(0)));
	input_event(input, EV_KEY, BTN_TL2, !!(b8 & BIT(1)));
	input_event(input, EV_KEY, BTN_TR, !!(b8 & BIT(2)));
	input_event(input, EV_KEY, BTN_TL, !!(b8 & BIT(3)));
	input_event(input, EV_KEY, BTN_Y, !!(b8 & BIT(4)));
	input_event(input, EV_KEY, BTN_B, !!(b8 & BIT(5)));
	input_event(input, EV_KEY, BTN_X, !!(b8 & BIT(6)));
	input_event(input, EV_KEY, BTN_A, !!(b8 & BIT(7)));
	input_event(input, EV_KEY, BTN_SELECT, !!(b9 & BIT(4)));
	input_event(input, EV_KEY, BTN_MODE, !!(b9 & BIT(5)));
	input_event(input, EV_KEY, BTN_START, !!(b9 & BIT(6)));
	input_event(input, EV_KEY, BTN_GEAR_DOWN, !!(b9 & BIT(7)));
	input_event(input, EV_KEY, BTN_GEAR_UP, !!(b10 & BIT(0)));
	input_event(input, EV_KEY, BTN_THUMBR, !!(b10 & BIT(2)));
	input_event(input, EV_KEY, BTN_THUMBL, !!(b10 & BIT(6)));
	input_event(input, EV_KEY, BTN_THUMB, lpad_touched || lpad_and_joy);
	input_event(input, EV_KEY, BTN_THUMB2, !!(b10 & BIT(4)));
	input_event(input, EV_KEY, BTN_DPAD_UP, !!(b9 & BIT(0)));
	input_event(input, EV_KEY, BTN_DPAD_RIGHT, !!(b9 & BIT(1)));
	input_event(input, EV_KEY, BTN_DPAD_LEFT, !!(b9 & BIT(2)));
	input_event(input, EV_KEY, BTN_DPAD_DOWN, !!(b9 & BIT(3)));

	input_sync(input);
}