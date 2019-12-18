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
struct hl_device {int dummy; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct hl_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 long hl_get_current (struct hl_device*,int,int /*<<< orphan*/ ) ; 
 long hl_get_fan_speed (struct hl_device*,int,int /*<<< orphan*/ ) ; 
 long hl_get_pwm_info (struct hl_device*,int,int /*<<< orphan*/ ) ; 
 long hl_get_temperature (struct hl_device*,int,int /*<<< orphan*/ ) ; 
 long hl_get_voltage (struct hl_device*,int,int /*<<< orphan*/ ) ; 
#define  hwmon_curr 148 
#define  hwmon_curr_input 147 
#define  hwmon_curr_max 146 
#define  hwmon_curr_min 145 
#define  hwmon_fan 144 
#define  hwmon_fan_input 143 
#define  hwmon_fan_max 142 
#define  hwmon_fan_min 141 
#define  hwmon_in 140 
#define  hwmon_in_input 139 
#define  hwmon_in_max 138 
#define  hwmon_in_min 137 
#define  hwmon_pwm 136 
#define  hwmon_pwm_enable 135 
#define  hwmon_pwm_input 134 
#define  hwmon_temp 133 
#define  hwmon_temp_crit 132 
#define  hwmon_temp_crit_hyst 131 
#define  hwmon_temp_input 130 
#define  hwmon_temp_max 129 
#define  hwmon_temp_max_hyst 128 

__attribute__((used)) static int hl_read(struct device *dev, enum hwmon_sensor_types type,
			u32 attr, int channel, long *val)
{
	struct hl_device *hdev = dev_get_drvdata(dev);

	if (hl_device_disabled_or_in_reset(hdev))
		return -ENODEV;

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
		case hwmon_temp_max:
		case hwmon_temp_crit:
		case hwmon_temp_max_hyst:
		case hwmon_temp_crit_hyst:
			break;
		default:
			return -EINVAL;
		}

		*val = hl_get_temperature(hdev, channel, attr);
		break;
	case hwmon_in:
		switch (attr) {
		case hwmon_in_input:
		case hwmon_in_min:
		case hwmon_in_max:
			break;
		default:
			return -EINVAL;
		}

		*val = hl_get_voltage(hdev, channel, attr);
		break;
	case hwmon_curr:
		switch (attr) {
		case hwmon_curr_input:
		case hwmon_curr_min:
		case hwmon_curr_max:
			break;
		default:
			return -EINVAL;
		}

		*val = hl_get_current(hdev, channel, attr);
		break;
	case hwmon_fan:
		switch (attr) {
		case hwmon_fan_input:
		case hwmon_fan_min:
		case hwmon_fan_max:
			break;
		default:
			return -EINVAL;
		}
		*val = hl_get_fan_speed(hdev, channel, attr);
		break;
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
		case hwmon_pwm_enable:
			break;
		default:
			return -EINVAL;
		}
		*val = hl_get_pwm_info(hdev, channel, attr);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}