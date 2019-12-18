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
struct input_dev {char* name; int /*<<< orphan*/  keybit; } ;
struct hid_input {TYPE_2__* report; struct input_dev* input; } ;
struct hid_device {int dummy; } ;
struct TYPE_4__ {int maxfield; TYPE_1__** field; } ;
struct TYPE_3__ {int application; int /*<<< orphan*/  physical; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_0 ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
#define  HID_DG_PEN 129 
#define  HID_DG_TOUCHSCREEN 128 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ntrig_input_configured(struct hid_device *hid,
		struct hid_input *hidinput)

{
	struct input_dev *input = hidinput->input;

	if (hidinput->report->maxfield < 1)
		return 0;

	switch (hidinput->report->field[0]->application) {
	case HID_DG_PEN:
		input->name = "N-Trig Pen";
		break;
	case HID_DG_TOUCHSCREEN:
		/* These keys are redundant for fingers, clear them
		 * to prevent incorrect identification */
		__clear_bit(BTN_TOOL_PEN, input->keybit);
		__clear_bit(BTN_TOOL_FINGER, input->keybit);
		__clear_bit(BTN_0, input->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, input->keybit);
		/*
		 * The physical touchscreen (single touch)
		 * input has a value for physical, whereas
		 * the multitouch only has logical input
		 * fields.
		 */
		input->name = (hidinput->report->field[0]->physical) ?
							"N-Trig Touchscreen" :
							"N-Trig MultiTouch";
		break;
	}

	return 0;
}