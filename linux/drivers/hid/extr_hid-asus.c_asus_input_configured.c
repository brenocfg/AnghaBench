#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct input_dev {int /*<<< orphan*/  propbit; int /*<<< orphan*/  keybit; } ;
struct hid_input {TYPE_1__* report; struct input_dev* input; } ;
struct hid_device {int dummy; } ;
struct asus_drvdata {int quirks; scalar_t__ enable_backlight; struct input_dev* input; TYPE_2__* tp; } ;
struct TYPE_4__ {int contact_size; int /*<<< orphan*/  max_contacts; int /*<<< orphan*/  res_y; int /*<<< orphan*/  res_x; int /*<<< orphan*/  max_y; int /*<<< orphan*/  max_x; } ;
struct TYPE_3__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_TOOL_WIDTH ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  INPUT_MT_POINTER ; 
 int /*<<< orphan*/  INPUT_PROP_BUTTONPAD ; 
 int /*<<< orphan*/  MAX_PRESSURE ; 
 int /*<<< orphan*/  MAX_TOUCH_MAJOR ; 
 int QUIRK_T100CHI ; 
 scalar_t__ T100CHI_MOUSE_REPORT_ID ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ asus_kbd_register_leds (struct hid_device*) ; 
 int /*<<< orphan*/  asus_kbd_wmi_led_control_present (struct hid_device*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 struct asus_drvdata* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_input_configured(struct hid_device *hdev, struct hid_input *hi)
{
	struct input_dev *input = hi->input;
	struct asus_drvdata *drvdata = hid_get_drvdata(hdev);

	/* T100CHI uses MULTI_INPUT, bind the touchpad to the mouse hid_input */
	if (drvdata->quirks & QUIRK_T100CHI &&
	    hi->report->id != T100CHI_MOUSE_REPORT_ID)
		return 0;

	if (drvdata->tp) {
		int ret;

		input_set_abs_params(input, ABS_MT_POSITION_X, 0,
				     drvdata->tp->max_x, 0, 0);
		input_set_abs_params(input, ABS_MT_POSITION_Y, 0,
				     drvdata->tp->max_y, 0, 0);
		input_abs_set_res(input, ABS_MT_POSITION_X, drvdata->tp->res_x);
		input_abs_set_res(input, ABS_MT_POSITION_Y, drvdata->tp->res_y);

		if (drvdata->tp->contact_size >= 5) {
			input_set_abs_params(input, ABS_TOOL_WIDTH, 0,
					     MAX_TOUCH_MAJOR, 0, 0);
			input_set_abs_params(input, ABS_MT_TOUCH_MAJOR, 0,
					     MAX_TOUCH_MAJOR, 0, 0);
			input_set_abs_params(input, ABS_MT_PRESSURE, 0,
					      MAX_PRESSURE, 0, 0);
		}

		__set_bit(BTN_LEFT, input->keybit);
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

		ret = input_mt_init_slots(input, drvdata->tp->max_contacts,
					  INPUT_MT_POINTER);

		if (ret) {
			hid_err(hdev, "Asus input mt init slots failed: %d\n", ret);
			return ret;
		}
	}

	drvdata->input = input;

	if (drvdata->enable_backlight &&
	    !asus_kbd_wmi_led_control_present(hdev) &&
	    asus_kbd_register_leds(hdev))
		hid_warn(hdev, "Failed to initialize backlight.\n");

	return 0;
}