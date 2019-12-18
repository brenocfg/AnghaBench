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
 int POWER_SUPPLY_PROP_CURRENT_AVG ; 
 int POWER_SUPPLY_PROP_CURRENT_MAX ; 
 int POWER_SUPPLY_PROP_CURRENT_NOW ; 
#define  hwmon_curr_average 130 
#define  hwmon_curr_input 129 
#define  hwmon_curr_max 128 

__attribute__((used)) static int power_supply_hwmon_curr_to_property(u32 attr)
{
	switch (attr) {
	case hwmon_curr_average:
		return POWER_SUPPLY_PROP_CURRENT_AVG;
	case hwmon_curr_max:
		return POWER_SUPPLY_PROP_CURRENT_MAX;
	case hwmon_curr_input:
		return POWER_SUPPLY_PROP_CURRENT_NOW;
	default:
		return -EINVAL;
	}
}