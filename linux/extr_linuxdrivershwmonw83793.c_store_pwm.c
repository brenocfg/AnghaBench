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
struct w83793_data {unsigned long* pwm_stop_time; int** pwm; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute_2 {int nr; int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PWM_STOP_TIME ; 
 unsigned long TIME_TO_REG (unsigned long) ; 
 int /*<<< orphan*/  W83793_REG_PWM (int,int) ; 
 int /*<<< orphan*/  W83793_REG_PWM_STOP_TIME (int) ; 
 int clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct w83793_data* i2c_get_clientdata (struct i2c_client*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int w83793_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83793_write_value (struct i2c_client*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static ssize_t
store_pwm(struct device *dev, struct device_attribute *attr,
	  const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct w83793_data *data = i2c_get_clientdata(client);
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	if (nr == PWM_STOP_TIME) {
		val = TIME_TO_REG(val);
		data->pwm_stop_time[index] = val;
		w83793_write_value(client, W83793_REG_PWM_STOP_TIME(index),
				   val);
	} else {
		val = clamp_val(val, 0, 0xff) >> 2;
		data->pwm[index][nr] =
		    w83793_read_value(client, W83793_REG_PWM(index, nr)) & 0xc0;
		data->pwm[index][nr] |= val;
		w83793_write_value(client, W83793_REG_PWM(index, nr),
							data->pwm[index][nr]);
	}

	mutex_unlock(&data->update_lock);
	return count;
}