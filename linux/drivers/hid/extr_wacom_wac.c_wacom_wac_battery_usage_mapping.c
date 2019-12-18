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
struct wacom_features {int /*<<< orphan*/  quirks; } ;
struct wacom_wac {struct wacom_features features; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_usage {int /*<<< orphan*/  hid; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
#define  HID_DG_BATTERYSTRENGTH 130 
#define  WACOM_HID_WD_BATTERY_CHARGING 129 
#define  WACOM_HID_WD_BATTERY_LEVEL 128 
 int /*<<< orphan*/  WACOM_QUIRK_BATTERY ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 unsigned int wacom_equivalent_usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_wac_battery_usage_mapping(struct hid_device *hdev,
		struct hid_field *field, struct hid_usage *usage)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_features *features = &wacom_wac->features;
	unsigned equivalent_usage = wacom_equivalent_usage(usage->hid);

	switch (equivalent_usage) {
	case HID_DG_BATTERYSTRENGTH:
	case WACOM_HID_WD_BATTERY_LEVEL:
	case WACOM_HID_WD_BATTERY_CHARGING:
		features->quirks |= WACOM_QUIRK_BATTERY;
		break;
	}
}