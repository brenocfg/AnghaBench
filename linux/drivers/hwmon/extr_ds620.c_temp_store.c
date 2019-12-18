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
struct sensor_device_attribute {size_t index; } ;
struct i2c_client {int dummy; } ;
struct ds620_data {long* temp; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DS620_REG_TEMP ; 
 int clamp_val (long,int,int) ; 
 struct ds620_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_store(struct device *dev, struct device_attribute *da,
			  const char *buf, size_t count)
{
	int res;
	long val;

	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct ds620_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;

	res = kstrtol(buf, 10, &val);

	if (res)
		return res;

	val = (clamp_val(val, -128000, 128000) * 10 / 625) * 8;

	mutex_lock(&data->update_lock);
	data->temp[attr->index] = val;
	i2c_smbus_write_word_swapped(client, DS620_REG_TEMP[attr->index],
				     data->temp[attr->index]);
	mutex_unlock(&data->update_lock);
	return count;
}