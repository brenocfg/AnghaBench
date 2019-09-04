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
struct w83793_data {long* temp_fan_map; int pwm_enable; int* temp_cruise; int* tolerance; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute_2 {int nr; int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int TEMP_CRUISE ; 
 int TEMP_FAN_MAP ; 
 int TEMP_PWM_ENABLE ; 
 int TEMP_TO_REG (long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  W83793_REG_PWM_ENABLE ; 
 int /*<<< orphan*/  W83793_REG_TEMP_CRUISE (int) ; 
 int /*<<< orphan*/  W83793_REG_TEMP_FAN_MAP (int) ; 
 int /*<<< orphan*/  W83793_REG_TEMP_TOL (int) ; 
 long clamp_val (long,int /*<<< orphan*/ ,int) ; 
 struct w83793_data* i2c_get_clientdata (struct i2c_client*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 void* w83793_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83793_write_value (struct i2c_client*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static ssize_t
store_sf_ctrl(struct device *dev, struct device_attribute *attr,
	      const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct w83793_data *data = i2c_get_clientdata(client);
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	if (nr == TEMP_FAN_MAP) {
		val = clamp_val(val, 0, 255);
		w83793_write_value(client, W83793_REG_TEMP_FAN_MAP(index), val);
		data->temp_fan_map[index] = val;
	} else if (nr == TEMP_PWM_ENABLE) {
		if (val == 2 || val == 3) {
			data->pwm_enable =
			    w83793_read_value(client, W83793_REG_PWM_ENABLE);
			if (val - 2)
				data->pwm_enable |= 1 << index;
			else
				data->pwm_enable &= ~(1 << index);
			w83793_write_value(client, W83793_REG_PWM_ENABLE,
							data->pwm_enable);
		} else {
			mutex_unlock(&data->update_lock);
			return -EINVAL;
		}
	} else if (nr == TEMP_CRUISE) {
		data->temp_cruise[index] =
		    w83793_read_value(client, W83793_REG_TEMP_CRUISE(index));
		data->temp_cruise[index] &= 0x80;
		data->temp_cruise[index] |= TEMP_TO_REG(val, 0, 0x7f);

		w83793_write_value(client, W83793_REG_TEMP_CRUISE(index),
						data->temp_cruise[index]);
	} else {		/* TEMP_TOLERANCE */
		int i = index >> 1;
		u8 shift = (index & 0x01) ? 4 : 0;
		data->tolerance[i] =
		    w83793_read_value(client, W83793_REG_TEMP_TOL(i));

		data->tolerance[i] &= ~(0x0f << shift);
		data->tolerance[i] |= TEMP_TO_REG(val, 0, 0x0f) << shift;
		w83793_write_value(client, W83793_REG_TEMP_TOL(i),
							data->tolerance[i]);
	}

	mutex_unlock(&data->update_lock);
	return count;
}