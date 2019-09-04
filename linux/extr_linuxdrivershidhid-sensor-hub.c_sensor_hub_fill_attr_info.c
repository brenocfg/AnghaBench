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
struct hid_sensor_hub_attribute_info {int size; int /*<<< orphan*/  logical_maximum; int /*<<< orphan*/  logical_minimum; int /*<<< orphan*/  unit_expo; int /*<<< orphan*/  units; void* report_id; void* index; } ;
struct hid_field {int report_size; int report_count; int /*<<< orphan*/  logical_maximum; int /*<<< orphan*/  logical_minimum; int /*<<< orphan*/  unit_exponent; int /*<<< orphan*/  unit; } ;
typedef  void* s32 ;

/* Variables and functions */

__attribute__((used)) static void sensor_hub_fill_attr_info(
		struct hid_sensor_hub_attribute_info *info,
		s32 index, s32 report_id, struct hid_field *field)
{
	info->index = index;
	info->report_id = report_id;
	info->units = field->unit;
	info->unit_expo = field->unit_exponent;
	info->size = (field->report_size * field->report_count)/8;
	info->logical_minimum = field->logical_minimum;
	info->logical_maximum = field->logical_maximum;
}