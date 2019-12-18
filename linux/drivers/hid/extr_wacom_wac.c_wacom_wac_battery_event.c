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
struct TYPE_2__ {int battery_capacity; int bat_connected; int bat_charging; int ps_connected; void* bat_status; } ;
struct wacom_wac {TYPE_1__ hid_data; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_usage {int /*<<< orphan*/  hid; } ;
struct hid_field {int logical_maximum; int logical_minimum; } ;
struct hid_device {int dummy; } ;
typedef  int __s32 ;

/* Variables and functions */
#define  HID_DG_BATTERYSTRENGTH 130 
 void* POWER_SUPPLY_STATUS_UNKNOWN ; 
#define  WACOM_HID_WD_BATTERY_CHARGING 129 
#define  WACOM_HID_WD_BATTERY_LEVEL 128 
 void* WACOM_POWER_SUPPLY_STATUS_AUTO ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 unsigned int wacom_equivalent_usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_wac_battery_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	unsigned equivalent_usage = wacom_equivalent_usage(usage->hid);

	switch (equivalent_usage) {
	case HID_DG_BATTERYSTRENGTH:
		if (value == 0) {
			wacom_wac->hid_data.bat_status = POWER_SUPPLY_STATUS_UNKNOWN;
		}
		else {
			value = value * 100 / (field->logical_maximum - field->logical_minimum);
			wacom_wac->hid_data.battery_capacity = value;
			wacom_wac->hid_data.bat_connected = 1;
			wacom_wac->hid_data.bat_status = WACOM_POWER_SUPPLY_STATUS_AUTO;
		}
		break;
	case WACOM_HID_WD_BATTERY_LEVEL:
		value = value * 100 / (field->logical_maximum - field->logical_minimum);
		wacom_wac->hid_data.battery_capacity = value;
		wacom_wac->hid_data.bat_connected = 1;
		wacom_wac->hid_data.bat_status = WACOM_POWER_SUPPLY_STATUS_AUTO;
		break;
	case WACOM_HID_WD_BATTERY_CHARGING:
		wacom_wac->hid_data.bat_charging = value;
		wacom_wac->hid_data.ps_connected = value;
		wacom_wac->hid_data.bat_connected = 1;
		wacom_wac->hid_data.bat_status = WACOM_POWER_SUPPLY_STATUS_AUTO;
		break;
	}
}