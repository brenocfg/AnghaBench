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
struct w83795_data {unsigned long* fan_min; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute_2 {int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  W83795_REG_FAN_MIN_HL (int) ; 
 int /*<<< orphan*/  W83795_REG_FAN_MIN_LSB (int) ; 
 unsigned long fan_to_reg (unsigned long) ; 
 struct w83795_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int w83795_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83795_write (struct i2c_client*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static ssize_t
store_fan_min(struct device *dev, struct device_attribute *attr,
	      const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int index = sensor_attr->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct w83795_data *data = i2c_get_clientdata(client);
	unsigned long val;

	if (kstrtoul(buf, 10, &val))
		return -EINVAL;
	val = fan_to_reg(val);

	mutex_lock(&data->update_lock);
	data->fan_min[index] = val;
	w83795_write(client, W83795_REG_FAN_MIN_HL(index), (val >> 4) & 0xff);
	val &= 0x0f;
	if (index & 1) {
		val <<= 4;
		val |= w83795_read(client, W83795_REG_FAN_MIN_LSB(index))
		       & 0x0f;
	} else {
		val |= w83795_read(client, W83795_REG_FAN_MIN_LSB(index))
		       & 0xf0;
	}
	w83795_write(client, W83795_REG_FAN_MIN_LSB(index), val & 0xff);
	mutex_unlock(&data->update_lock);

	return count;
}