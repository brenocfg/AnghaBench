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
struct max1668_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp_min; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX1668_REG_LIML_WR (int) ; 
 int /*<<< orphan*/  clamp_val (long,int,int) ; 
 struct max1668_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_temp_min(struct device *dev,
			    struct device_attribute *devattr,
			    const char *buf, size_t count)
{
	int index = to_sensor_dev_attr(devattr)->index;
	struct max1668_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long temp;
	int ret;

	ret = kstrtol(buf, 10, &temp);
	if (ret < 0)
		return ret;

	mutex_lock(&data->update_lock);
	data->temp_min[index] = clamp_val(temp/1000, -128, 127);
	ret = i2c_smbus_write_byte_data(client,
					MAX1668_REG_LIML_WR(index),
					data->temp_min[index]);
	if (ret < 0)
		count = ret;
	mutex_unlock(&data->update_lock);

	return count;
}