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
struct wacom_features {scalar_t__ type; int /*<<< orphan*/  pressure_max; int /*<<< orphan*/  unitExpo; int /*<<< orphan*/  unit; int /*<<< orphan*/  y_phy; int /*<<< orphan*/  y_max; int /*<<< orphan*/  x_phy; int /*<<< orphan*/  x_max; int /*<<< orphan*/  device_type; } ;
struct TYPE_2__ {struct wacom_features features; } ;
struct wacom {TYPE_1__ wacom_wac; } ;
struct hid_usage {int /*<<< orphan*/  hid; } ;
struct hid_field {int /*<<< orphan*/  logical_maximum; int /*<<< orphan*/  unit_exponent; int /*<<< orphan*/  unit; int /*<<< orphan*/  physical_maximum; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAMBOO_PT ; 
 scalar_t__ BAMBOO_TOUCH ; 
#define  HID_DG_TIPPRESSURE 130 
#define  HID_GD_X 129 
#define  HID_GD_Y 128 
 scalar_t__ HID_GENERIC ; 
 int /*<<< orphan*/  WACOM_DEVICETYPE_PEN ; 
 int /*<<< orphan*/  WACOM_DEVICETYPE_TOUCH ; 
 int WACOM_FINGER_FIELD (struct hid_field*) ; 
 int WACOM_PEN_FIELD (struct hid_field*) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 unsigned int wacom_equivalent_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_hid_usage_quirk (struct hid_device*,struct hid_field*,struct hid_usage*) ; 
 int /*<<< orphan*/  wacom_wac_usage_mapping (struct hid_device*,struct hid_field*,struct hid_usage*) ; 

__attribute__((used)) static void wacom_usage_mapping(struct hid_device *hdev,
		struct hid_field *field, struct hid_usage *usage)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_features *features = &wacom->wacom_wac.features;
	bool finger = WACOM_FINGER_FIELD(field);
	bool pen = WACOM_PEN_FIELD(field);
	unsigned equivalent_usage = wacom_equivalent_usage(usage->hid);

	/*
	* Requiring Stylus Usage will ignore boot mouse
	* X/Y values and some cases of invalid Digitizer X/Y
	* values commonly reported.
	*/
	if (pen)
		features->device_type |= WACOM_DEVICETYPE_PEN;
	else if (finger)
		features->device_type |= WACOM_DEVICETYPE_TOUCH;
	else
		return;

	wacom_hid_usage_quirk(hdev, field, usage);

	switch (equivalent_usage) {
	case HID_GD_X:
		features->x_max = field->logical_maximum;
		if (finger) {
			features->x_phy = field->physical_maximum;
			if ((features->type != BAMBOO_PT) &&
			    (features->type != BAMBOO_TOUCH)) {
				features->unit = field->unit;
				features->unitExpo = field->unit_exponent;
			}
		}
		break;
	case HID_GD_Y:
		features->y_max = field->logical_maximum;
		if (finger) {
			features->y_phy = field->physical_maximum;
			if ((features->type != BAMBOO_PT) &&
			    (features->type != BAMBOO_TOUCH)) {
				features->unit = field->unit;
				features->unitExpo = field->unit_exponent;
			}
		}
		break;
	case HID_DG_TIPPRESSURE:
		if (pen)
			features->pressure_max = field->logical_maximum;
		break;
	}

	if (features->type == HID_GENERIC)
		wacom_wac_usage_mapping(hdev, field, usage);
}