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
typedef  int u8 ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1031_data {int conf1; int* old_pwm; int* pwm; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int ADM1031_CONF1_AUTO_MODE ; 
 int /*<<< orphan*/  ADM1031_REG_CONF1 ; 
 int /*<<< orphan*/  ADM1031_REG_PWM ; 
 void* FAN_CHAN_TO_REG (int,int) ; 
 int /*<<< orphan*/  adm1031_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct adm1031_data* dev_get_drvdata (struct device*) ; 
 int get_fan_auto_nearest (struct adm1031_data*,int,long,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
fan_auto_channel_store(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct adm1031_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int nr = to_sensor_dev_attr(attr)->index;
	long val;
	u8 reg;
	int ret;
	u8 old_fan_mode;

	ret = kstrtol(buf, 10, &val);
	if (ret)
		return ret;

	old_fan_mode = data->conf1;

	mutex_lock(&data->update_lock);

	ret = get_fan_auto_nearest(data, nr, val, data->conf1);
	if (ret < 0) {
		mutex_unlock(&data->update_lock);
		return ret;
	}
	reg = ret;
	data->conf1 = FAN_CHAN_TO_REG(reg, data->conf1);
	if ((data->conf1 & ADM1031_CONF1_AUTO_MODE) ^
	    (old_fan_mode & ADM1031_CONF1_AUTO_MODE)) {
		if (data->conf1 & ADM1031_CONF1_AUTO_MODE) {
			/*
			 * Switch to Auto Fan Mode
			 * Save PWM registers
			 * Set PWM registers to 33% Both
			 */
			data->old_pwm[0] = data->pwm[0];
			data->old_pwm[1] = data->pwm[1];
			adm1031_write_value(client, ADM1031_REG_PWM, 0x55);
		} else {
			/* Switch to Manual Mode */
			data->pwm[0] = data->old_pwm[0];
			data->pwm[1] = data->old_pwm[1];
			/* Restore PWM registers */
			adm1031_write_value(client, ADM1031_REG_PWM,
					    data->pwm[0] | (data->pwm[1] << 4));
		}
	}
	data->conf1 = FAN_CHAN_TO_REG(reg, data->conf1);
	adm1031_write_value(client, ADM1031_REG_CONF1, data->conf1);
	mutex_unlock(&data->update_lock);
	return count;
}