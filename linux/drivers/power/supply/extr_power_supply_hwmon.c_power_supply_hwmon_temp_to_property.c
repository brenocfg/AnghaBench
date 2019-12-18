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
 int POWER_SUPPLY_PROP_TEMP ; 
 int POWER_SUPPLY_PROP_TEMP_ALERT_MAX ; 
 int POWER_SUPPLY_PROP_TEMP_ALERT_MIN ; 
 int POWER_SUPPLY_PROP_TEMP_AMBIENT ; 
 int POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX ; 
 int POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN ; 
 int POWER_SUPPLY_PROP_TEMP_MAX ; 
 int POWER_SUPPLY_PROP_TEMP_MIN ; 
#define  hwmon_temp_input 132 
#define  hwmon_temp_max 131 
#define  hwmon_temp_max_alarm 130 
#define  hwmon_temp_min 129 
#define  hwmon_temp_min_alarm 128 

__attribute__((used)) static int power_supply_hwmon_temp_to_property(u32 attr, int channel)
{
	if (channel) {
		switch (attr) {
		case hwmon_temp_input:
			return POWER_SUPPLY_PROP_TEMP_AMBIENT;
		case hwmon_temp_min_alarm:
			return POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN;
		case hwmon_temp_max_alarm:
			return POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX;
		default:
			break;
		}
	} else {
		switch (attr) {
		case hwmon_temp_input:
			return POWER_SUPPLY_PROP_TEMP;
		case hwmon_temp_max:
			return POWER_SUPPLY_PROP_TEMP_MAX;
		case hwmon_temp_min:
			return POWER_SUPPLY_PROP_TEMP_MIN;
		case hwmon_temp_min_alarm:
			return POWER_SUPPLY_PROP_TEMP_ALERT_MIN;
		case hwmon_temp_max_alarm:
			return POWER_SUPPLY_PROP_TEMP_ALERT_MAX;
		default:
			break;
		}
	}

	return -EINVAL;
}