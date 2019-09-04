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
 int hwmon_chip ; 
 int hwmon_chip_update_interval ; 
 int hwmon_temp ; 
#define  hwmon_temp_input 134 
#define  hwmon_temp_max 133 
#define  hwmon_temp_max_alarm 132 
#define  hwmon_temp_max_hyst 131 
#define  hwmon_temp_min 130 
#define  hwmon_temp_min_alarm 129 
#define  hwmon_temp_min_hyst 128 

__attribute__((used)) static umode_t tmp108_is_visible(const void *data, enum hwmon_sensor_types type,
				 u32 attr, int channel)
{
	if (type == hwmon_chip && attr == hwmon_chip_update_interval)
		return 0644;

	if (type != hwmon_temp)
		return 0;

	switch (attr) {
	case hwmon_temp_input:
	case hwmon_temp_min_alarm:
	case hwmon_temp_max_alarm:
		return 0444;
	case hwmon_temp_min:
	case hwmon_temp_max:
	case hwmon_temp_min_hyst:
	case hwmon_temp_max_hyst:
		return 0644;
	default:
		return 0;
	}
}