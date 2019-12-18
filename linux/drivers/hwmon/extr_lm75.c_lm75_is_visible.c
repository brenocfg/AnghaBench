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
typedef  int umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct lm75_data {TYPE_1__* params; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;
struct TYPE_2__ {int num_sample_times; } ;

/* Variables and functions */
#define  hwmon_chip 133 
#define  hwmon_chip_update_interval 132 
#define  hwmon_temp 131 
#define  hwmon_temp_input 130 
#define  hwmon_temp_max 129 
#define  hwmon_temp_max_hyst 128 

__attribute__((used)) static umode_t lm75_is_visible(const void *data, enum hwmon_sensor_types type,
			       u32 attr, int channel)
{
	const struct lm75_data *config_data = data;

	switch (type) {
	case hwmon_chip:
		switch (attr) {
		case hwmon_chip_update_interval:
			if (config_data->params->num_sample_times > 1)
				return 0644;
			return 0444;
		}
		break;
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
			return 0444;
		case hwmon_temp_max:
		case hwmon_temp_max_hyst:
			return 0644;
		}
		break;
	default:
		break;
	}
	return 0;
}