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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct max6650_data {int config; int /*<<< orphan*/  update_lock; void* count; int /*<<< orphan*/  client; void* dac; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 long ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MAX6650_CFG_V12 ; 
 int /*<<< orphan*/  MAX6650_REG_COUNT ; 
 int /*<<< orphan*/  MAX6650_REG_DAC ; 
 int /*<<< orphan*/  clamp_val (long,int /*<<< orphan*/ ,int) ; 
 struct max6650_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_fan 133 
#define  hwmon_fan_div 132 
#define  hwmon_fan_target 131 
#define  hwmon_pwm 130 
#define  hwmon_pwm_enable 129 
#define  hwmon_pwm_input 128 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * max6650_pwm_modes ; 
 int max6650_set_operating_mode (struct max6650_data*,int /*<<< orphan*/ ) ; 
 int max6650_set_target (struct max6650_data*,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* pwm_to_dac (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max6650_write(struct device *dev, enum hwmon_sensor_types type,
			 u32 attr, int channel, long val)
{
	struct max6650_data *data = dev_get_drvdata(dev);
	int ret = 0;
	u8 reg;

	mutex_lock(&data->update_lock);

	switch (type) {
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
			reg = pwm_to_dac(clamp_val(val, 0, 255),
					 data->config & MAX6650_CFG_V12);
			ret = i2c_smbus_write_byte_data(data->client,
							MAX6650_REG_DAC, reg);
			if (ret)
				break;
			data->dac = reg;
			break;
		case hwmon_pwm_enable:
			if (val < 0 || val >= ARRAY_SIZE(max6650_pwm_modes)) {
				ret = -EINVAL;
				break;
			}
			ret = max6650_set_operating_mode(data,
						max6650_pwm_modes[val]);
			break;
		default:
			ret = -EOPNOTSUPP;
			break;
		}
		break;
	case hwmon_fan:
		switch (attr) {
		case hwmon_fan_div:
			switch (val) {
			case 1:
				reg = 0;
				break;
			case 2:
				reg = 1;
				break;
			case 4:
				reg = 2;
				break;
			case 8:
				reg = 3;
				break;
			default:
				ret = -EINVAL;
				goto error;
			}
			ret = i2c_smbus_write_byte_data(data->client,
							MAX6650_REG_COUNT, reg);
			if (ret)
				break;
			data->count = reg;
			break;
		case hwmon_fan_target:
			if (val < 0) {
				ret = -EINVAL;
				break;
			}
			ret = max6650_set_target(data, val);
			break;
		default:
			ret = -EOPNOTSUPP;
			break;
		}
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}

error:
	mutex_unlock(&data->update_lock);
	return ret;
}