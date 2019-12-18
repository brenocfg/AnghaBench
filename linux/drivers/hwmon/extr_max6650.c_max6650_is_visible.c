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
struct max6650_data {int nr_fans; int alarm_en; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int MAX6650_ALRM_MAX ; 
 int MAX6650_ALRM_MIN ; 
 int MAX6650_ALRM_TACH ; 
#define  hwmon_fan 137 
#define  hwmon_fan_div 136 
#define  hwmon_fan_fault 135 
#define  hwmon_fan_input 134 
#define  hwmon_fan_max_alarm 133 
#define  hwmon_fan_min_alarm 132 
#define  hwmon_fan_target 131 
#define  hwmon_pwm 130 
#define  hwmon_pwm_enable 129 
#define  hwmon_pwm_input 128 

__attribute__((used)) static umode_t max6650_is_visible(const void *_data,
				  enum hwmon_sensor_types type, u32 attr,
				  int channel)
{
	const struct max6650_data *data = _data;

	if (channel && (channel >= data->nr_fans || type != hwmon_fan))
		return 0;

	switch (type) {
	case hwmon_fan:
		switch (attr) {
		case hwmon_fan_input:
			return 0444;
		case hwmon_fan_target:
		case hwmon_fan_div:
			return 0644;
		case hwmon_fan_min_alarm:
			if (data->alarm_en & MAX6650_ALRM_MIN)
				return 0444;
			break;
		case hwmon_fan_max_alarm:
			if (data->alarm_en & MAX6650_ALRM_MAX)
				return 0444;
			break;
		case hwmon_fan_fault:
			if (data->alarm_en & MAX6650_ALRM_TACH)
				return 0444;
			break;
		default:
			break;
		}
		break;
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
		case hwmon_pwm_enable:
			return 0644;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return 0;
}