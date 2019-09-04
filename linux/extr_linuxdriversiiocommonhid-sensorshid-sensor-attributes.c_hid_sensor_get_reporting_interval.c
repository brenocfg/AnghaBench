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
typedef  int /*<<< orphan*/  u32 ;
struct hid_sensor_hub_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ units; } ;
struct hid_sensor_common {int poll_interval; TYPE_1__ poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_PROP_REPORT_INTERVAL ; 
 scalar_t__ HID_USAGE_SENSOR_UNITS_MILLISECOND ; 
 int /*<<< orphan*/  sensor_hub_input_get_attribute_info (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
int hid_sensor_get_reporting_interval(struct hid_sensor_hub_device *hsdev,
					u32 usage_id,
					struct hid_sensor_common *st)
{
	sensor_hub_input_get_attribute_info(hsdev,
					HID_FEATURE_REPORT, usage_id,
					HID_USAGE_SENSOR_PROP_REPORT_INTERVAL,
					&st->poll);
	/* Default unit of measure is milliseconds */
	if (st->poll.units == 0)
		st->poll.units = HID_USAGE_SENSOR_UNITS_MILLISECOND;

	st->poll_interval = -1;

	return 0;

}