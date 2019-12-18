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
 int EINVAL ; 
#define  hwmon_curr 130 
#define  hwmon_in 129 
#define  hwmon_temp 128 
 int power_supply_hwmon_curr_to_property (int /*<<< orphan*/ ) ; 
 int power_supply_hwmon_in_to_property (int /*<<< orphan*/ ) ; 
 int power_supply_hwmon_temp_to_property (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
power_supply_hwmon_to_property(enum hwmon_sensor_types type,
			       u32 attr, int channel)
{
	switch (type) {
	case hwmon_in:
		return power_supply_hwmon_in_to_property(attr);
	case hwmon_curr:
		return power_supply_hwmon_curr_to_property(attr);
	case hwmon_temp:
		return power_supply_hwmon_temp_to_property(attr, channel);
	default:
		return -EINVAL;
	}
}