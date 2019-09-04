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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct asb100_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * fan_min; int /*<<< orphan*/ * fan_div; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASB100_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAN_TO_REG (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asb100_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct asb100_data* i2c_get_clientdata (struct i2c_client*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan_min(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct asb100_data *data = i2c_get_clientdata(client);
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_div[nr]));
	asb100_write_value(client, ASB100_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	return count;
}