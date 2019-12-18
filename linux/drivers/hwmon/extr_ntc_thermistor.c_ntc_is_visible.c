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
 int hwmon_temp ; 
#define  hwmon_temp_input 129 
#define  hwmon_temp_type 128 

__attribute__((used)) static umode_t ntc_is_visible(const void *data, enum hwmon_sensor_types type,
			      u32 attr, int channel)
{
	if (type == hwmon_temp) {
		switch (attr) {
		case hwmon_temp_input:
		case hwmon_temp_type:
			return 0444;
		default:
			break;
		}
	}
	return 0;
}