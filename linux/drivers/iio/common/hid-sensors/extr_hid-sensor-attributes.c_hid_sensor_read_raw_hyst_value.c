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
struct TYPE_2__ {int /*<<< orphan*/  unit_expo; int /*<<< orphan*/  size; int /*<<< orphan*/  index; int /*<<< orphan*/  report_id; } ;
struct hid_sensor_common {TYPE_1__ sensitivity; int /*<<< orphan*/  hsdev; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  convert_from_vtf_format (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int sensor_hub_get_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 

int hid_sensor_read_raw_hyst_value(struct hid_sensor_common *st,
				int *val1, int *val2)
{
	s32 value;
	int ret;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->sensitivity.report_id,
				     st->sensitivity.index, sizeof(value),
				     &value);
	if (ret < 0 || value < 0) {
		*val1 = *val2 = 0;
		return -EINVAL;
	} else {
		convert_from_vtf_format(value, st->sensitivity.size,
					st->sensitivity.unit_expo,
					val1, val2);
	}

	return IIO_VAL_INT_PLUS_MICRO;
}