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
struct w83793_data {int pwm_default; int pwm_uptime; int pwm_downtime; int temp_critical; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute_2 {int nr; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int SETUP_PWM_DEFAULT ; 
 int SETUP_PWM_DOWNTIME ; 
 int SETUP_PWM_UPTIME ; 
 int TEMP_TO_REG (long,int /*<<< orphan*/ ,int) ; 
 void* TIME_TO_REG (long) ; 
 int /*<<< orphan*/  W83793_REG_PWM_DEFAULT ; 
 int /*<<< orphan*/  W83793_REG_PWM_DOWNTIME ; 
 int /*<<< orphan*/  W83793_REG_PWM_UPTIME ; 
 int /*<<< orphan*/  W83793_REG_TEMP_CRITICAL ; 
 int clamp_val (long,int /*<<< orphan*/ ,int) ; 
 struct w83793_data* i2c_get_clientdata (struct i2c_client*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int w83793_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83793_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_sf_setup(struct device *dev, struct device_attribute *attr,
	       const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	struct i2c_client *client = to_i2c_client(dev);
	struct w83793_data *data = i2c_get_clientdata(client);
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	if (nr == SETUP_PWM_DEFAULT) {
		data->pwm_default =
		    w83793_read_value(client, W83793_REG_PWM_DEFAULT) & 0xc0;
		data->pwm_default |= clamp_val(val, 0, 0xff) >> 2;
		w83793_write_value(client, W83793_REG_PWM_DEFAULT,
							data->pwm_default);
	} else if (nr == SETUP_PWM_UPTIME) {
		data->pwm_uptime = TIME_TO_REG(val);
		data->pwm_uptime += data->pwm_uptime == 0 ? 1 : 0;
		w83793_write_value(client, W83793_REG_PWM_UPTIME,
							data->pwm_uptime);
	} else if (nr == SETUP_PWM_DOWNTIME) {
		data->pwm_downtime = TIME_TO_REG(val);
		data->pwm_downtime += data->pwm_downtime == 0 ? 1 : 0;
		w83793_write_value(client, W83793_REG_PWM_DOWNTIME,
							data->pwm_downtime);
	} else {		/* SETUP_TEMP_CRITICAL */
		data->temp_critical =
		    w83793_read_value(client, W83793_REG_TEMP_CRITICAL) & 0x80;
		data->temp_critical |= TEMP_TO_REG(val, 0, 0x7f);
		w83793_write_value(client, W83793_REG_TEMP_CRITICAL,
							data->temp_critical);
	}

	mutex_unlock(&data->update_lock);
	return count;
}