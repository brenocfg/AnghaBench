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
typedef  int u8 ;
typedef  int u32 ;
struct max31790_data {long* pwm; int* fan_config; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MAX31790_FAN_CFG_RPM_MODE ; 
 int MAX31790_FAN_CFG_TACH_INPUT_EN ; 
 int /*<<< orphan*/  MAX31790_REG_FAN_CONFIG (int) ; 
 int /*<<< orphan*/  MAX31790_REG_PWMOUT (int) ; 
 struct max31790_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_pwm_enable 129 
#define  hwmon_pwm_input 128 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max31790_write_pwm(struct device *dev, u32 attr, int channel,
			      long val)
{
	struct max31790_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u8 fan_config;
	int err = 0;

	mutex_lock(&data->update_lock);

	switch (attr) {
	case hwmon_pwm_input:
		if (val < 0 || val > 255) {
			err = -EINVAL;
			break;
		}
		data->pwm[channel] = val << 8;
		err = i2c_smbus_write_word_swapped(client,
						   MAX31790_REG_PWMOUT(channel),
						   data->pwm[channel]);
		break;
	case hwmon_pwm_enable:
		fan_config = data->fan_config[channel];
		if (val == 0) {
			fan_config &= ~(MAX31790_FAN_CFG_TACH_INPUT_EN |
					MAX31790_FAN_CFG_RPM_MODE);
		} else if (val == 1) {
			fan_config = (fan_config |
				      MAX31790_FAN_CFG_TACH_INPUT_EN) &
				     ~MAX31790_FAN_CFG_RPM_MODE;
		} else if (val == 2) {
			fan_config |= MAX31790_FAN_CFG_TACH_INPUT_EN |
				      MAX31790_FAN_CFG_RPM_MODE;
		} else {
			err = -EINVAL;
			break;
		}
		data->fan_config[channel] = fan_config;
		err = i2c_smbus_write_byte_data(client,
					MAX31790_REG_FAN_CONFIG(channel),
					fan_config);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	mutex_unlock(&data->update_lock);

	return err;
}