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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
#define  hwmon_curr 130 
 int /*<<< orphan*/  hwmon_curr_max ; 
#define  hwmon_in 129 
 int /*<<< orphan*/  hwmon_in_max ; 
 int /*<<< orphan*/  hwmon_in_min ; 
#define  hwmon_temp 128 
 int /*<<< orphan*/  hwmon_temp_max ; 
 int /*<<< orphan*/  hwmon_temp_max_alarm ; 
 int /*<<< orphan*/  hwmon_temp_min ; 
 int /*<<< orphan*/  hwmon_temp_min_alarm ; 

__attribute__((used)) static bool power_supply_hwmon_is_writable(enum hwmon_sensor_types type,
					   u32 attr)
{
	switch (type) {
	case hwmon_in:
		return attr == hwmon_in_min ||
		       attr == hwmon_in_max;
	case hwmon_curr:
		return attr == hwmon_curr_max;
	case hwmon_temp:
		return attr == hwmon_temp_max ||
		       attr == hwmon_temp_min ||
		       attr == hwmon_temp_min_alarm ||
		       attr == hwmon_temp_max_alarm;
	default:
		return false;
	}
}