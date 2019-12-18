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
typedef  int umode_t ;
typedef  int u32 ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int hwmon_power ; 
#define  hwmon_power_input 132 
#define  hwmon_power_max 131 
 int hwmon_temp ; 
#define  hwmon_temp_crit 130 
#define  hwmon_temp_input 129 
#define  hwmon_temp_max 128 

__attribute__((used)) static umode_t
nfp_hwmon_is_visible(const void *data, enum hwmon_sensor_types type, u32 attr,
		     int channel)
{
	if (type == hwmon_temp) {
		switch (attr) {
		case hwmon_temp_input:
		case hwmon_temp_crit:
		case hwmon_temp_max:
			return 0444;
		}
	} else if (type == hwmon_power) {
		switch (attr) {
		case hwmon_power_input:
		case hwmon_power_max:
			return 0444;
		}
	}
	return 0;
}