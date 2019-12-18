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
typedef  int /*<<< orphan*/  value ;
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  report_id; int /*<<< orphan*/  unit_expo; int /*<<< orphan*/  size; } ;
struct hid_sensor_common {scalar_t__ raw_hystersis; TYPE_1__ sensitivity; int /*<<< orphan*/  hsdev; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ convert_to_vtf_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int sensor_hub_get_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int sensor_hub_set_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 

int hid_sensor_write_raw_hyst_value(struct hid_sensor_common *st,
					int val1, int val2)
{
	s32 value;
	int ret;

	if (val1 < 0 || val2 < 0)
		return -EINVAL;

	value = convert_to_vtf_format(st->sensitivity.size,
				st->sensitivity.unit_expo,
				val1, val2);
	ret = sensor_hub_set_feature(st->hsdev, st->sensitivity.report_id,
				     st->sensitivity.index, sizeof(value),
				     &value);
	if (ret < 0 || value < 0)
		return -EINVAL;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->sensitivity.report_id,
				     st->sensitivity.index, sizeof(value),
				     &value);
	if (ret < 0 || value < 0)
		return -EINVAL;

	st->raw_hystersis = value;

	return 0;
}