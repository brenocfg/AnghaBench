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
struct w83795_data {int temp_mode; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute_2 {int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  W83795_REG_TEMP_CTRL2 ; 
 struct w83795_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int w83795_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83795_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_temp_mode(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct w83795_data *data = i2c_get_clientdata(client);
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int index = sensor_attr->index;
	int reg_shift;
	unsigned long val;
	u8 tmp;

	if (kstrtoul(buf, 10, &val) < 0)
		return -EINVAL;
	if ((val != 4) && (val != 3))
		return -EINVAL;

	mutex_lock(&data->update_lock);
	if (val == 3) {
		/* Thermal diode */
		val = 0x01;
		data->temp_mode |= 1 << index;
	} else if (val == 4) {
		/* Thermistor */
		val = 0x03;
		data->temp_mode &= ~(1 << index);
	}

	reg_shift = 2 * index;
	tmp = w83795_read(client, W83795_REG_TEMP_CTRL2);
	tmp &= ~(0x03 << reg_shift);
	tmp |= val << reg_shift;
	w83795_write(client, W83795_REG_TEMP_CTRL2, tmp);

	mutex_unlock(&data->update_lock);
	return count;
}