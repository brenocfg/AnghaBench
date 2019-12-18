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
struct TYPE_2__ {scalar_t__ touch_input; scalar_t__ pen_input; } ;
struct wacom {TYPE_1__ wacom_wac; } ;
struct hid_report {scalar_t__ type; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HID_INPUT_REPORT ; 
 scalar_t__ WACOM_FINGER_FIELD (struct hid_field*) ; 
 scalar_t__ WACOM_PEN_FIELD (struct hid_field*) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  wacom_report_events (struct hid_device*,struct hid_report*,int,int) ; 
 int /*<<< orphan*/  wacom_set_num_expected (struct hid_device*,struct hid_report*,int,struct hid_field*,int) ; 
 int /*<<< orphan*/  wacom_wac_finger_report (struct hid_device*,struct hid_report*) ; 
 int /*<<< orphan*/  wacom_wac_pen_report (struct hid_device*,struct hid_report*) ; 

__attribute__((used)) static int wacom_wac_collection(struct hid_device *hdev, struct hid_report *report,
			 int collection_index, struct hid_field *field,
			 int field_index)
{
	struct wacom *wacom = hid_get_drvdata(hdev);

	if (WACOM_FINGER_FIELD(field))
		wacom_set_num_expected(hdev, report, collection_index, field,
				       field_index);
	wacom_report_events(hdev, report, collection_index, field_index);

	/*
	 * Non-input reports may be sent prior to the device being
	 * completely initialized. Since only their events need
	 * to be processed, exit after 'wacom_report_events' has
	 * been called to prevent potential crashes in the report-
	 * processing functions.
	 */
	if (report->type != HID_INPUT_REPORT)
		return -1;

	if (WACOM_PEN_FIELD(field) && wacom->wacom_wac.pen_input)
		wacom_wac_pen_report(hdev, report);
	else if (WACOM_FINGER_FIELD(field) && wacom->wacom_wac.touch_input)
		wacom_wac_finger_report(hdev, report);

	return 0;
}