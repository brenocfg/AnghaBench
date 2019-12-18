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
typedef  int u32 ;
struct sensor_device_attribute {int index; } ;
struct ina209_data {int valid; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 struct ina209_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ina209_reset_history_regs ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ina209_history_store(struct device *dev,
				    struct device_attribute *da,
				    const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct ina209_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u32 mask = attr->index;
	long val;
	int i, ret;

	ret = kstrtol(buf, 10, &val);
	if (ret < 0)
		return ret;

	mutex_lock(&data->update_lock);
	for (i = 0; i < ARRAY_SIZE(ina209_reset_history_regs); i++) {
		if (mask & (1 << i))
			i2c_smbus_write_word_swapped(client,
					ina209_reset_history_regs[i], 1);
	}
	data->valid = false;
	mutex_unlock(&data->update_lock);
	return count;
}