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
struct hid_usage {scalar_t__ hid; } ;
struct hid_report {int maxfield; TYPE_1__** field; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_2__ {int report_count; int maxusage; int /*<<< orphan*/ * value; struct hid_usage* usage; int /*<<< orphan*/  logical_minimum; int /*<<< orphan*/  logical_maximum; } ;

/* Variables and functions */
 scalar_t__ HID_GD_RESOLUTION_MULTIPLIER ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_wait (struct hid_device*) ; 

__attribute__((used)) static bool __hidinput_change_resolution_multipliers(struct hid_device *hid,
		struct hid_report *report, bool use_logical_max)
{
	struct hid_usage *usage;
	bool update_needed = false;
	int i, j;

	if (report->maxfield == 0)
		return false;

	/*
	 * If we have more than one feature within this report we
	 * need to fill in the bits from the others before we can
	 * overwrite the ones for the Resolution Multiplier.
	 */
	if (report->maxfield > 1) {
		hid_hw_request(hid, report, HID_REQ_GET_REPORT);
		hid_hw_wait(hid);
	}

	for (i = 0; i < report->maxfield; i++) {
		__s32 value = use_logical_max ?
			      report->field[i]->logical_maximum :
			      report->field[i]->logical_minimum;

		/* There is no good reason for a Resolution
		 * Multiplier to have a count other than 1.
		 * Ignore that case.
		 */
		if (report->field[i]->report_count != 1)
			continue;

		for (j = 0; j < report->field[i]->maxusage; j++) {
			usage = &report->field[i]->usage[j];

			if (usage->hid != HID_GD_RESOLUTION_MULTIPLIER)
				continue;

			report->field[i]->value[j] = value;
			update_needed = true;
		}
	}

	return update_needed;
}