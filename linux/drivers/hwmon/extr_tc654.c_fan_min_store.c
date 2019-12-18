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
struct tc654_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * fan_fault; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TC654_FAN_FAULT_TO_REG (unsigned long) ; 
 int /*<<< orphan*/  TC654_REG_FAN_FAULT (int) ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct tc654_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_min_store(struct device *dev, struct device_attribute *da,
			     const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(da)->index;
	struct tc654_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long val;
	int ret;

	if (kstrtoul(buf, 10, &val))
		return -EINVAL;

	val = clamp_val(val, 0, 12750);

	mutex_lock(&data->update_lock);

	data->fan_fault[nr] = TC654_FAN_FAULT_TO_REG(val);
	ret = i2c_smbus_write_byte_data(client, TC654_REG_FAN_FAULT(nr),
					data->fan_fault[nr]);

	mutex_unlock(&data->update_lock);
	return ret < 0 ? ret : count;
}