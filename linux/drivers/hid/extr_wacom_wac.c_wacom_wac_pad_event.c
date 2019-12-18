#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int inrange_state; int pad_input_event_flag; } ;
struct wacom_features {int /*<<< orphan*/  numbered_buttons; } ;
struct wacom_wac {int is_direct_mode; TYPE_3__ hid_data; TYPE_1__* shared; struct wacom_features features; struct input_dev* pad_input; } ;
struct TYPE_5__ {int count; } ;
struct wacom {TYPE_2__ led; struct wacom_wac wacom_wac; } ;
struct input_dev {int dummy; } ;
struct hid_usage {scalar_t__ hid; int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct hid_field {scalar_t__ physical; int /*<<< orphan*/  logical_maximum; } ;
struct hid_device {int vendor; int product; } ;
typedef  int __s32 ;
struct TYPE_4__ {int is_touch_on; int /*<<< orphan*/  touch_input; } ;

/* Variables and functions */
 unsigned int HID_DG_TABLETFUNCTIONKEY ; 
 int /*<<< orphan*/  SW_MUTE_DEVICE ; 
#define  WACOM_HID_WD_BUTTONCENTER 133 
#define  WACOM_HID_WD_MODE_CHANGE 132 
#define  WACOM_HID_WD_MUTE_DEVICE 131 
#define  WACOM_HID_WD_TOUCHONOFF 130 
#define  WACOM_HID_WD_TOUCHRING 129 
#define  WACOM_HID_WD_TOUCHRINGSTATUS 128 
 int /*<<< orphan*/  WACOM_WORKER_MODE_CHANGE ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 unsigned int wacom_equivalent_usage (scalar_t__) ; 
 int wacom_offset_rotation (struct input_dev*,struct hid_usage*,int,int,int) ; 
 int /*<<< orphan*/  wacom_schedule_work (struct wacom_wac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_update_led (struct wacom*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wacom_wac_pad_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct input_dev *input = wacom_wac->pad_input;
	struct wacom_features *features = &wacom_wac->features;
	unsigned equivalent_usage = wacom_equivalent_usage(usage->hid);
	int i;
	bool do_report = false;

	/*
	 * Avoid reporting this event and setting inrange_state if this usage
	 * hasn't been mapped.
	 */
	if (!usage->type && equivalent_usage != WACOM_HID_WD_MODE_CHANGE)
		return;

	if (wacom_equivalent_usage(field->physical) == HID_DG_TABLETFUNCTIONKEY) {
		if (usage->hid != WACOM_HID_WD_TOUCHRING)
			wacom_wac->hid_data.inrange_state |= value;
	}

	switch (equivalent_usage) {
	case WACOM_HID_WD_TOUCHRING:
		/*
		 * Userspace expects touchrings to increase in value with
		 * clockwise gestures and have their zero point at the
		 * tablet's left. HID events "should" be clockwise-
		 * increasing and zero at top, though the MobileStudio
		 * Pro and 2nd-gen Intuos Pro don't do this...
		 */
		if (hdev->vendor == 0x56a &&
		    (hdev->product == 0x34d || hdev->product == 0x34e ||  /* MobileStudio Pro */
		     hdev->product == 0x357 || hdev->product == 0x358 ||  /* Intuos Pro 2 */
		     hdev->product == 0x392 ||				  /* Intuos Pro 2 */
		     hdev->product == 0x398 || hdev->product == 0x399)) { /* MobileStudio Pro */
			value = (field->logical_maximum - value);

			if (hdev->product == 0x357 || hdev->product == 0x358 ||
			    hdev->product == 0x392)
				value = wacom_offset_rotation(input, usage, value, 3, 16);
			else if (hdev->product == 0x34d || hdev->product == 0x34e ||
				 hdev->product == 0x398 || hdev->product == 0x399)
				value = wacom_offset_rotation(input, usage, value, 1, 2);
		}
		else {
			value = wacom_offset_rotation(input, usage, value, 1, 4);
		}
		do_report = true;
		break;
	case WACOM_HID_WD_TOUCHRINGSTATUS:
		if (!value)
			input_event(input, usage->type, usage->code, 0);
		break;

	case WACOM_HID_WD_MUTE_DEVICE:
	case WACOM_HID_WD_TOUCHONOFF:
		if (wacom_wac->shared->touch_input) {
			bool *is_touch_on = &wacom_wac->shared->is_touch_on;

			if (equivalent_usage == WACOM_HID_WD_MUTE_DEVICE && value)
				*is_touch_on = !(*is_touch_on);
			else if (equivalent_usage == WACOM_HID_WD_TOUCHONOFF)
				*is_touch_on = value;

			input_report_switch(wacom_wac->shared->touch_input,
					    SW_MUTE_DEVICE, !(*is_touch_on));
			input_sync(wacom_wac->shared->touch_input);
		}
		break;

	case WACOM_HID_WD_MODE_CHANGE:
		if (wacom_wac->is_direct_mode != value) {
			wacom_wac->is_direct_mode = value;
			wacom_schedule_work(&wacom->wacom_wac, WACOM_WORKER_MODE_CHANGE);
		}
		break;

	case WACOM_HID_WD_BUTTONCENTER:
		for (i = 0; i < wacom->led.count; i++)
			wacom_update_led(wacom, features->numbered_buttons,
					 value, i);
		 /* fall through*/
	default:
		do_report = true;
		break;
	}

	if (do_report) {
		input_event(input, usage->type, usage->code, value);
		if (value)
			wacom_wac->hid_data.pad_input_event_flag = true;
	}
}