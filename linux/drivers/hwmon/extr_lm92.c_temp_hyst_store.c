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
struct lm92_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM92_REG_TEMP_HYST ; 
 scalar_t__ TEMP_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEMP_TO_REG (scalar_t__) ; 
 long clamp_val (long,int,int) ; 
 struct lm92_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t t_hyst ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_hyst_store(struct device *dev,
			       struct device_attribute *devattr,
			       const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct lm92_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	val = clamp_val(val, -120000, 220000);
	mutex_lock(&data->update_lock);
	data->temp[t_hyst] =
		TEMP_TO_REG(TEMP_FROM_REG(data->temp[attr->index]) - val);
	i2c_smbus_write_word_swapped(client, LM92_REG_TEMP_HYST,
				     data->temp[t_hyst]);
	mutex_unlock(&data->update_lock);
	return count;
}