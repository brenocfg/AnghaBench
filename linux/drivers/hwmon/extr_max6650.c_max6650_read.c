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
struct max6650_data {int config; int* tach; int count; int alarm; int valid; int /*<<< orphan*/  speed; int /*<<< orphan*/  dac; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int DIV_FROM_REG (int) ; 
 long DIV_ROUND_CLOSEST (int,int) ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct max6650_data*) ; 
 int MAX6650_ALRM_MAX ; 
 int MAX6650_ALRM_MIN ; 
 int MAX6650_ALRM_TACH ; 
 int MAX6650_CFG_MODE_MASK ; 
 int MAX6650_CFG_V12 ; 
 int PTR_ERR (struct max6650_data*) ; 
 int clock ; 
 long dac_to_pwm (int /*<<< orphan*/ ,int) ; 
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
 struct max6650_data* max6650_update_device (struct device*) ; 

__attribute__((used)) static int max6650_read(struct device *dev, enum hwmon_sensor_types type,
			u32 attr, int channel, long *val)
{
	struct max6650_data *data = max6650_update_device(dev);
	int mode;

	if (IS_ERR(data))
		return PTR_ERR(data);

	switch (type) {
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
			*val = dac_to_pwm(data->dac,
					  data->config & MAX6650_CFG_V12);
			break;
		case hwmon_pwm_enable:
			/*
			 * Possible values:
			 * 0 = Fan always on
			 * 1 = Open loop, Voltage is set according to speed,
			 *     not regulated.
			 * 2 = Closed loop, RPM for all fans regulated by fan1
			 *     tachometer
			 * 3 = Fan off
			 */
			mode = (data->config & MAX6650_CFG_MODE_MASK) >> 4;
			*val = (4 - mode) & 3; /* {0 1 2 3} -> {0 3 2 1} */
			break;
		default:
			return -EOPNOTSUPP;
		}
		break;
	case hwmon_fan:
		switch (attr) {
		case hwmon_fan_input:
			/*
			 * Calculation details:
			 *
			 * Each tachometer counts over an interval given by the
			 * "count" register (0.25, 0.5, 1 or 2 seconds).
			 * The driver assumes that the fans produce two pulses
			 * per revolution (this seems to be the most common).
			 */
			*val = DIV_ROUND_CLOSEST(data->tach[channel] * 120,
						 DIV_FROM_REG(data->count));
			break;
		case hwmon_fan_div:
			*val = DIV_FROM_REG(data->count);
			break;
		case hwmon_fan_target:
			/*
			 * Use the datasheet equation:
			 *    FanSpeed = KSCALE x fCLK / [256 x (KTACH + 1)]
			 * then multiply by 60 to give rpm.
			 */
			*val = 60 * DIV_FROM_REG(data->config) * clock /
				(256 * (data->speed + 1));
			break;
		case hwmon_fan_min_alarm:
			*val = !!(data->alarm & MAX6650_ALRM_MIN);
			data->alarm &= ~MAX6650_ALRM_MIN;
			data->valid = false;
			break;
		case hwmon_fan_max_alarm:
			*val = !!(data->alarm & MAX6650_ALRM_MAX);
			data->alarm &= ~MAX6650_ALRM_MAX;
			data->valid = false;
			break;
		case hwmon_fan_fault:
			*val = !!(data->alarm & MAX6650_ALRM_TACH);
			data->alarm &= ~MAX6650_ALRM_TACH;
			data->valid = false;
			break;
		default:
			return -EOPNOTSUPP;
		}
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}