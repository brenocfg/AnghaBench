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
struct TYPE_2__ {unsigned int last_slot_field; void* tipswitch; void* id; void* height; void* width; void* y; void* x; } ;
struct wacom_features {void* touch_max; } ;
struct wacom_wac {int is_invalid_bt_frame; int /*<<< orphan*/  touch_input; TYPE_1__ hid_data; struct wacom_features features; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_usage {scalar_t__ usage_index; int /*<<< orphan*/  hid; } ;
struct hid_field {scalar_t__ report_count; } ;
struct hid_device {int dummy; } ;
typedef  void* __s32 ;

/* Variables and functions */
#define  HID_DG_CONTACTID 135 
#define  HID_DG_CONTACTMAX 134 
#define  HID_DG_HEIGHT 133 
#define  HID_DG_TIPSWITCH 132 
#define  HID_DG_WIDTH 131 
#define  HID_GD_X 130 
#define  HID_GD_Y 129 
#define  WACOM_HID_WT_REPORT_VALID 128 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 unsigned int wacom_equivalent_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_wac_finger_slot (struct wacom_wac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_wac_finger_event(struct hid_device *hdev,
		struct hid_field *field, struct hid_usage *usage, __s32 value)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	unsigned equivalent_usage = wacom_equivalent_usage(usage->hid);
	struct wacom_features *features = &wacom->wacom_wac.features;

	if (wacom_wac->is_invalid_bt_frame)
		return;

	switch (equivalent_usage) {
	case HID_GD_X:
		wacom_wac->hid_data.x = value;
		break;
	case HID_GD_Y:
		wacom_wac->hid_data.y = value;
		break;
	case HID_DG_WIDTH:
		wacom_wac->hid_data.width = value;
		break;
	case HID_DG_HEIGHT:
		wacom_wac->hid_data.height = value;
		break;
	case HID_DG_CONTACTID:
		wacom_wac->hid_data.id = value;
		break;
	case HID_DG_TIPSWITCH:
		wacom_wac->hid_data.tipswitch = value;
		break;
	case WACOM_HID_WT_REPORT_VALID:
		wacom_wac->is_invalid_bt_frame = !value;
		return;
	case HID_DG_CONTACTMAX:
		features->touch_max = value;
		return;
	}

	if (usage->usage_index + 1 == field->report_count) {
		if (equivalent_usage == wacom_wac->hid_data.last_slot_field)
			wacom_wac_finger_slot(wacom_wac, wacom_wac->touch_input);
	}
}