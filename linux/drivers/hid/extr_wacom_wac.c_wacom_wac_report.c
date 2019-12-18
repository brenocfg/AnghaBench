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
struct TYPE_3__ {scalar_t__ type; } ;
struct wacom_wac {scalar_t__ pad_input; scalar_t__ touch_input; scalar_t__ pen_input; TYPE_1__ features; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_report {int maxfield; struct hid_field** field; } ;
struct hid_field {TYPE_2__* usage; int /*<<< orphan*/  physical; } ;
struct hid_device {int dummy; } ;
struct TYPE_4__ {int collection_index; } ;

/* Variables and functions */
 scalar_t__ HID_DG_TABLETFUNCTIONKEY ; 
 scalar_t__ HID_GENERIC ; 
 scalar_t__ WACOM_FINGER_FIELD (struct hid_field*) ; 
 scalar_t__ WACOM_PAD_FIELD (struct hid_field*) ; 
 scalar_t__ WACOM_PEN_FIELD (struct hid_field*) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ wacom_equivalent_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_wac_battery_pre_report (struct hid_device*,struct hid_report*) ; 
 int /*<<< orphan*/  wacom_wac_battery_report (struct hid_device*,struct hid_report*) ; 
 scalar_t__ wacom_wac_collection (struct hid_device*,struct hid_report*,int,struct hid_field*,int) ; 
 int /*<<< orphan*/  wacom_wac_finger_pre_report (struct hid_device*,struct hid_report*) ; 
 int /*<<< orphan*/  wacom_wac_pad_pre_report (struct hid_device*,struct hid_report*) ; 
 int /*<<< orphan*/  wacom_wac_pad_report (struct hid_device*,struct hid_report*,struct hid_field*) ; 
 int /*<<< orphan*/  wacom_wac_pen_pre_report (struct hid_device*,struct hid_report*) ; 

void wacom_wac_report(struct hid_device *hdev, struct hid_report *report)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct hid_field *field;
	bool pad_in_hid_field = false, pen_in_hid_field = false,
		finger_in_hid_field = false, true_pad = false;
	int r;
	int prev_collection = -1;

	if (wacom_wac->features.type != HID_GENERIC)
		return;

	for (r = 0; r < report->maxfield; r++) {
		field = report->field[r];

		if (WACOM_PAD_FIELD(field))
			pad_in_hid_field = true;
		if (WACOM_PEN_FIELD(field))
			pen_in_hid_field = true;
		if (WACOM_FINGER_FIELD(field))
			finger_in_hid_field = true;
		if (wacom_equivalent_usage(field->physical) == HID_DG_TABLETFUNCTIONKEY)
			true_pad = true;
	}

	wacom_wac_battery_pre_report(hdev, report);

	if (pad_in_hid_field && wacom->wacom_wac.pad_input)
		wacom_wac_pad_pre_report(hdev, report);
	if (pen_in_hid_field && wacom->wacom_wac.pen_input)
		wacom_wac_pen_pre_report(hdev, report);
	if (finger_in_hid_field && wacom->wacom_wac.touch_input)
		wacom_wac_finger_pre_report(hdev, report);

	for (r = 0; r < report->maxfield; r++) {
		field = report->field[r];

		if (field->usage[0].collection_index != prev_collection) {
			if (wacom_wac_collection(hdev, report,
				field->usage[0].collection_index, field, r) < 0)
				return;
			prev_collection = field->usage[0].collection_index;
		}
	}

	wacom_wac_battery_report(hdev, report);

	if (true_pad && wacom->wacom_wac.pad_input)
		wacom_wac_pad_report(hdev, report, field);
}