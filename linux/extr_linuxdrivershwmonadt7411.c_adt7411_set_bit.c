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
struct sensor_device_attribute_2 {int /*<<< orphan*/  nr; int /*<<< orphan*/  index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7411_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  next_update; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int adt7411_modify_bit (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct adt7411_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t adt7411_set_bit(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t count)
{
	struct sensor_device_attribute_2 *s_attr2 = to_sensor_dev_attr_2(attr);
	struct adt7411_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int ret;
	unsigned long flag;

	ret = kstrtoul(buf, 0, &flag);
	if (ret || flag > 1)
		return -EINVAL;

	ret = adt7411_modify_bit(client, s_attr2->index, s_attr2->nr, flag);

	/* force update */
	mutex_lock(&data->update_lock);
	data->next_update = jiffies;
	mutex_unlock(&data->update_lock);

	return ret < 0 ? ret : count;
}