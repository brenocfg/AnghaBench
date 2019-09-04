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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
#define  hwmon_chip 133 
#define  hwmon_chip_update_interval 132 
#define  hwmon_temp 131 
#define  hwmon_temp_input 130 
#define  hwmon_temp_max 129 
#define  hwmon_temp_max_hyst 128 

__attribute__((used)) static umode_t lm75_is_visible(const void *data, enum hwmon_sensor_types type,
			       u32 attr, int channel)
{
	switch (type) {
	case hwmon_chip:
		switch (attr) {
		case hwmon_chip_update_interval:
			return S_IRUGO;
		}
		break;
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
			return S_IRUGO;
		case hwmon_temp_max:
		case hwmon_temp_max_hyst:
			return S_IRUGO | S_IWUSR;
		}
		break;
	default:
		break;
	}
	return 0;
}