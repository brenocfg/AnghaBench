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
struct hid_usage {int dummy; } ;
struct hid_report {scalar_t__ maxfield; struct hid_field** field; int /*<<< orphan*/  device; } ;
struct hid_field {size_t index; struct hid_report* report; struct hid_usage* usage; int /*<<< orphan*/ * value; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HID_MAX_FIELDS ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*) ; 
 struct hid_field* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hid_field *hid_register_field(struct hid_report *report, unsigned usages, unsigned values)
{
	struct hid_field *field;

	if (report->maxfield == HID_MAX_FIELDS) {
		hid_err(report->device, "too many fields in report\n");
		return NULL;
	}

	field = kzalloc((sizeof(struct hid_field) +
			 usages * sizeof(struct hid_usage) +
			 values * sizeof(unsigned)), GFP_KERNEL);
	if (!field)
		return NULL;

	field->index = report->maxfield++;
	report->field[field->index] = field;
	field->usage = (struct hid_usage *)(field + 1);
	field->value = (s32 *)(field->usage + usages);
	field->report = report;

	return field;
}