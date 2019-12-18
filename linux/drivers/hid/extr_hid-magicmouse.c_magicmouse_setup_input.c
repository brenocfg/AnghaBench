#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ product; } ;
struct input_dev {char* name; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  evbit; TYPE_1__ id; int /*<<< orphan*/  propbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  relbit; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_0 ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_MOUSE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_QUADTAP ; 
 int /*<<< orphan*/  BTN_TOOL_QUINTTAP ; 
 int /*<<< orphan*/  BTN_TOOL_TRIPLETAP ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REL ; 
 int INPUT_MT_DROP_UNUSED ; 
 int INPUT_MT_POINTER ; 
 int INPUT_MT_TRACK ; 
 int /*<<< orphan*/  INPUT_PROP_BUTTONPAD ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
 int MOUSE_MAX_X ; 
 int MOUSE_MAX_Y ; 
 int MOUSE_MIN_X ; 
 int MOUSE_MIN_Y ; 
 int /*<<< orphan*/  MOUSE_RES_X ; 
 int /*<<< orphan*/  MOUSE_RES_Y ; 
 int /*<<< orphan*/  MSC_RAW ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int TRACKPAD2_MAX_X ; 
 int TRACKPAD2_MAX_Y ; 
 int TRACKPAD2_MIN_X ; 
 int TRACKPAD2_MIN_Y ; 
 int /*<<< orphan*/  TRACKPAD2_RES_X ; 
 int /*<<< orphan*/  TRACKPAD2_RES_Y ; 
 int TRACKPAD_MAX_X ; 
 int TRACKPAD_MAX_Y ; 
 int TRACKPAD_MIN_X ; 
 int TRACKPAD_MIN_Y ; 
 int /*<<< orphan*/  TRACKPAD_RES_X ; 
 int /*<<< orphan*/  TRACKPAD_RES_Y ; 
 scalar_t__ USB_DEVICE_ID_APPLE_MAGICMOUSE ; 
 scalar_t__ USB_DEVICE_ID_APPLE_MAGICTRACKPAD2 ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ emulate_3button ; 
 scalar_t__ emulate_scroll_wheel ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_mt_init_slots (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_events_per_packet (struct input_dev*,int) ; 
 scalar_t__ report_undeciphered ; 

__attribute__((used)) static int magicmouse_setup_input(struct input_dev *input, struct hid_device *hdev)
{
	int error;
	int mt_flags = 0;

	__set_bit(EV_KEY, input->evbit);

	if (input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE) {
		__set_bit(BTN_LEFT, input->keybit);
		__set_bit(BTN_RIGHT, input->keybit);
		if (emulate_3button)
			__set_bit(BTN_MIDDLE, input->keybit);

		__set_bit(EV_REL, input->evbit);
		__set_bit(REL_X, input->relbit);
		__set_bit(REL_Y, input->relbit);
		if (emulate_scroll_wheel) {
			__set_bit(REL_WHEEL, input->relbit);
			__set_bit(REL_HWHEEL, input->relbit);
		}
	} else if (input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) {
		/* setting the device name to ensure the same driver settings
		 * get loaded, whether connected through bluetooth or USB
		 */
		input->name = "Apple Inc. Magic Trackpad 2";

		__clear_bit(EV_MSC, input->evbit);
		__clear_bit(BTN_0, input->keybit);
		__clear_bit(BTN_RIGHT, input->keybit);
		__clear_bit(BTN_MIDDLE, input->keybit);
		__set_bit(BTN_MOUSE, input->keybit);
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);
		__set_bit(BTN_TOOL_FINGER, input->keybit);

		mt_flags = INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED |
				INPUT_MT_TRACK;
	} else { /* USB_DEVICE_ID_APPLE_MAGICTRACKPAD */
		/* input->keybit is initialized with incorrect button info
		 * for Magic Trackpad. There really is only one physical
		 * button (BTN_LEFT == BTN_MOUSE). Make sure we don't
		 * advertise buttons that don't exist...
		 */
		__clear_bit(BTN_RIGHT, input->keybit);
		__clear_bit(BTN_MIDDLE, input->keybit);
		__set_bit(BTN_MOUSE, input->keybit);
		__set_bit(BTN_TOOL_FINGER, input->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, input->keybit);
		__set_bit(BTN_TOOL_TRIPLETAP, input->keybit);
		__set_bit(BTN_TOOL_QUADTAP, input->keybit);
		__set_bit(BTN_TOOL_QUINTTAP, input->keybit);
		__set_bit(BTN_TOUCH, input->keybit);
		__set_bit(INPUT_PROP_POINTER, input->propbit);
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);
	}


	__set_bit(EV_ABS, input->evbit);

	error = input_mt_init_slots(input, 16, mt_flags);
	if (error)
		return error;
	input_set_abs_params(input, ABS_MT_TOUCH_MAJOR, 0, 255 << 2,
			     4, 0);
	input_set_abs_params(input, ABS_MT_TOUCH_MINOR, 0, 255 << 2,
			     4, 0);

	/* Note: Touch Y position from the device is inverted relative
	 * to how pointer motion is reported (and relative to how USB
	 * HID recommends the coordinates work).  This driver keeps
	 * the origin at the same position, and just uses the additive
	 * inverse of the reported Y.
	 */
	if (input->id.product == USB_DEVICE_ID_APPLE_MAGICMOUSE) {
		input_set_abs_params(input, ABS_MT_ORIENTATION, -31, 32, 1, 0);
		input_set_abs_params(input, ABS_MT_POSITION_X,
				     MOUSE_MIN_X, MOUSE_MAX_X, 4, 0);
		input_set_abs_params(input, ABS_MT_POSITION_Y,
				     MOUSE_MIN_Y, MOUSE_MAX_Y, 4, 0);

		input_abs_set_res(input, ABS_MT_POSITION_X,
				  MOUSE_RES_X);
		input_abs_set_res(input, ABS_MT_POSITION_Y,
				  MOUSE_RES_Y);
	} else if (input->id.product ==  USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) {
		input_set_abs_params(input, ABS_MT_PRESSURE, 0, 253, 0, 0);
		input_set_abs_params(input, ABS_PRESSURE, 0, 253, 0, 0);
		input_set_abs_params(input, ABS_MT_ORIENTATION, -3, 4, 0, 0);
		input_set_abs_params(input, ABS_X, TRACKPAD2_MIN_X,
				     TRACKPAD2_MAX_X, 0, 0);
		input_set_abs_params(input, ABS_Y, TRACKPAD2_MIN_Y,
				     TRACKPAD2_MAX_Y, 0, 0);
		input_set_abs_params(input, ABS_MT_POSITION_X,
				     TRACKPAD2_MIN_X, TRACKPAD2_MAX_X, 0, 0);
		input_set_abs_params(input, ABS_MT_POSITION_Y,
				     TRACKPAD2_MIN_Y, TRACKPAD2_MAX_Y, 0, 0);

		input_abs_set_res(input, ABS_X, TRACKPAD2_RES_X);
		input_abs_set_res(input, ABS_Y, TRACKPAD2_RES_Y);
		input_abs_set_res(input, ABS_MT_POSITION_X, TRACKPAD2_RES_X);
		input_abs_set_res(input, ABS_MT_POSITION_Y, TRACKPAD2_RES_Y);
	} else { /* USB_DEVICE_ID_APPLE_MAGICTRACKPAD */
		input_set_abs_params(input, ABS_MT_ORIENTATION, -31, 32, 1, 0);
		input_set_abs_params(input, ABS_X, TRACKPAD_MIN_X,
				     TRACKPAD_MAX_X, 4, 0);
		input_set_abs_params(input, ABS_Y, TRACKPAD_MIN_Y,
				     TRACKPAD_MAX_Y, 4, 0);
		input_set_abs_params(input, ABS_MT_POSITION_X,
				     TRACKPAD_MIN_X, TRACKPAD_MAX_X, 4, 0);
		input_set_abs_params(input, ABS_MT_POSITION_Y,
				     TRACKPAD_MIN_Y, TRACKPAD_MAX_Y, 4, 0);

		input_abs_set_res(input, ABS_X, TRACKPAD_RES_X);
		input_abs_set_res(input, ABS_Y, TRACKPAD_RES_Y);
		input_abs_set_res(input, ABS_MT_POSITION_X,
				  TRACKPAD_RES_X);
		input_abs_set_res(input, ABS_MT_POSITION_Y,
				  TRACKPAD_RES_Y);
	}

	input_set_events_per_packet(input, 60);

	if (report_undeciphered &&
	    input->id.product != USB_DEVICE_ID_APPLE_MAGICTRACKPAD2) {
		__set_bit(EV_MSC, input->evbit);
		__set_bit(MSC_RAW, input->mscbit);
	}

	return 0;
}