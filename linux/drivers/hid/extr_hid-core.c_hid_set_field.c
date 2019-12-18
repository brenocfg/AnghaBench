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
struct hid_field {unsigned int report_size; unsigned int report_count; scalar_t__ logical_minimum; scalar_t__* value; TYPE_1__* report; scalar_t__ usage; } ;
typedef  scalar_t__ __s32 ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_dump_input (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  s32ton (scalar_t__,unsigned int) ; 
 scalar_t__ snto32 (int /*<<< orphan*/ ,unsigned int) ; 

int hid_set_field(struct hid_field *field, unsigned offset, __s32 value)
{
	unsigned size;

	if (!field)
		return -1;

	size = field->report_size;

	hid_dump_input(field->report->device, field->usage + offset, value);

	if (offset >= field->report_count) {
		hid_err(field->report->device, "offset (%d) exceeds report_count (%d)\n",
				offset, field->report_count);
		return -1;
	}
	if (field->logical_minimum < 0) {
		if (value != snto32(s32ton(value, size), size)) {
			hid_err(field->report->device, "value %d is out of range\n", value);
			return -1;
		}
	}
	field->value[offset] = value;
	return 0;
}