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
struct hid_report_id {scalar_t__ report_type; } ;
struct hid_report {scalar_t__ type; } ;
struct hid_device {TYPE_1__* driver; } ;
struct TYPE_2__ {struct hid_report_id* report_table; } ;

/* Variables and functions */
 scalar_t__ HID_ANY_ID ; 
 scalar_t__ HID_TERMINATOR ; 

__attribute__((used)) static int hid_match_report(struct hid_device *hid, struct hid_report *report)
{
	const struct hid_report_id *id = hid->driver->report_table;

	if (!id) /* NULL means all */
		return 1;

	for (; id->report_type != HID_TERMINATOR; id++)
		if (id->report_type == HID_ANY_ID ||
				id->report_type == report->type)
			return 1;
	return 0;
}