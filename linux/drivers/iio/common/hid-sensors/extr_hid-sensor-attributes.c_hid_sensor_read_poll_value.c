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
struct TYPE_2__ {scalar_t__ units; int /*<<< orphan*/  index; int /*<<< orphan*/  report_id; } ;
struct hid_sensor_common {TYPE_1__ poll; int /*<<< orphan*/  hsdev; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HID_USAGE_SENSOR_UNITS_SECOND ; 
 int sensor_hub_get_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

s32 hid_sensor_read_poll_value(struct hid_sensor_common *st)
{
	s32 value = 0;
	int ret;

	ret = sensor_hub_get_feature(st->hsdev,
				     st->poll.report_id,
				     st->poll.index, sizeof(value), &value);

	if (ret < 0 || value < 0) {
		return -EINVAL;
	} else {
		if (st->poll.units == HID_USAGE_SENSOR_UNITS_SECOND)
			value = value * 1000;
	}

	return value;
}