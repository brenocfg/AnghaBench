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
struct TYPE_2__ {int touch_max; } ;
struct hid_data {unsigned int last_slot_field; scalar_t__ cc_report; int cc_index; int cc_value_index; int num_expected; } ;
struct wacom_wac {TYPE_1__ features; struct hid_data hid_data; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_usage {int /*<<< orphan*/  hid; } ;
struct hid_report {int maxfield; scalar_t__ id; struct hid_field** field; } ;
struct hid_field {int maxusage; int* value; struct hid_usage* usage; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
#define  HID_DG_CONTACTCOUNT 136 
#define  HID_DG_CONTACTID 135 
#define  HID_DG_HEIGHT 134 
#define  HID_DG_INRANGE 133 
#define  HID_DG_INVERT 132 
#define  HID_DG_TIPSWITCH 131 
#define  HID_DG_WIDTH 130 
#define  HID_GD_X 129 
#define  HID_GD_Y 128 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 unsigned int wacom_equivalent_usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_wac_finger_pre_report(struct hid_device *hdev,
		struct hid_report *report)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct hid_data* hid_data = &wacom_wac->hid_data;
	int i;

	for (i = 0; i < report->maxfield; i++) {
		struct hid_field *field = report->field[i];
		int j;

		for (j = 0; j < field->maxusage; j++) {
			struct hid_usage *usage = &field->usage[j];
			unsigned int equivalent_usage =
				wacom_equivalent_usage(usage->hid);

			switch (equivalent_usage) {
			case HID_GD_X:
			case HID_GD_Y:
			case HID_DG_WIDTH:
			case HID_DG_HEIGHT:
			case HID_DG_CONTACTID:
			case HID_DG_INRANGE:
			case HID_DG_INVERT:
			case HID_DG_TIPSWITCH:
				hid_data->last_slot_field = equivalent_usage;
				break;
			case HID_DG_CONTACTCOUNT:
				hid_data->cc_report = report->id;
				hid_data->cc_index = i;
				hid_data->cc_value_index = j;
				break;
			}
		}
	}

	if (hid_data->cc_report != 0 &&
	    hid_data->cc_index >= 0) {
		struct hid_field *field = report->field[hid_data->cc_index];
		int value = field->value[hid_data->cc_value_index];
		if (value)
			hid_data->num_expected = value;
	}
	else {
		hid_data->num_expected = wacom_wac->features.touch_max;
	}
}