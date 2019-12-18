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
struct input_dev {int dummy; } ;
struct hid_usage {scalar_t__ type; scalar_t__ code; int hid; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int claimed; } ;
struct a4tech_sc {int quirks; int delayed_value; int hw_wheel; } ;
typedef  int __s32 ;
struct TYPE_2__ {struct input_dev* input; } ;

/* Variables and functions */
 int A4_2WHEEL_MOUSE_HACK_7 ; 
 int A4_2WHEEL_MOUSE_HACK_B8 ; 
 int A4_WHEEL_ORIENTATION ; 
 scalar_t__ EV_REL ; 
 int HID_CLAIMED_INPUT ; 
 scalar_t__ REL_HWHEEL ; 
 scalar_t__ REL_HWHEEL_HI_RES ; 
 scalar_t__ REL_WHEEL ; 
 scalar_t__ REL_WHEEL_HI_RES ; 
 struct a4tech_sc* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int a4_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	struct a4tech_sc *a4 = hid_get_drvdata(hdev);
	struct input_dev *input;

	if (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput)
		return 0;

	input = field->hidinput->input;

	if (a4->quirks & A4_2WHEEL_MOUSE_HACK_B8) {
		if (usage->type == EV_REL && usage->code == REL_WHEEL_HI_RES) {
			a4->delayed_value = value;
			return 1;
		}

		if (usage->hid == A4_WHEEL_ORIENTATION) {
			input_event(input, EV_REL, value ? REL_HWHEEL :
					REL_WHEEL, a4->delayed_value);
			input_event(input, EV_REL, value ? REL_HWHEEL_HI_RES :
					REL_WHEEL_HI_RES, a4->delayed_value * 120);
			return 1;
		}
	}

	if ((a4->quirks & A4_2WHEEL_MOUSE_HACK_7) && usage->hid == 0x00090007) {
		a4->hw_wheel = !!value;
		return 1;
	}

	if (usage->code == REL_WHEEL_HI_RES && a4->hw_wheel) {
		input_event(input, usage->type, REL_HWHEEL, value);
		input_event(input, usage->type, REL_HWHEEL_HI_RES, value * 120);
		return 1;
	}

	return 0;
}