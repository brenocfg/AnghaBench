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
struct hid_data {unsigned int last_slot_field; } ;
struct wacom_wac {int is_invalid_bt_frame; struct hid_data hid_data; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_usage {int /*<<< orphan*/  hid; } ;
struct hid_report {int maxfield; struct hid_field** field; } ;
struct hid_field {int maxusage; struct hid_usage* usage; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
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

	wacom_wac->is_invalid_bt_frame = false;

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
			}
		}
	}
}