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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_SUPPLY_PROP_VOLTAGE_AVG ; 
 int POWER_SUPPLY_PROP_VOLTAGE_MAX ; 
 int POWER_SUPPLY_PROP_VOLTAGE_MIN ; 
 int POWER_SUPPLY_PROP_VOLTAGE_NOW ; 
#define  hwmon_in_average 131 
#define  hwmon_in_input 130 
#define  hwmon_in_max 129 
#define  hwmon_in_min 128 

__attribute__((used)) static int power_supply_hwmon_in_to_property(u32 attr)
{
	switch (attr) {
	case hwmon_in_average:
		return POWER_SUPPLY_PROP_VOLTAGE_AVG;
	case hwmon_in_min:
		return POWER_SUPPLY_PROP_VOLTAGE_MIN;
	case hwmon_in_max:
		return POWER_SUPPLY_PROP_VOLTAGE_MAX;
	case hwmon_in_input:
		return POWER_SUPPLY_PROP_VOLTAGE_NOW;
	default:
		return -EINVAL;
	}
}