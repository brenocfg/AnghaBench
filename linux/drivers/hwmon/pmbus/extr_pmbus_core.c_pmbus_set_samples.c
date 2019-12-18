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
struct pmbus_samples_reg {TYPE_1__* attr; int /*<<< orphan*/  page; } ;
struct pmbus_data {int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int _pmbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 struct pmbus_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 struct pmbus_samples_reg* to_samples_reg (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pmbus_set_samples(struct device *dev,
				 struct device_attribute *devattr,
				 const char *buf, size_t count)
{
	int ret;
	long val;
	struct i2c_client *client = to_i2c_client(dev->parent);
	struct pmbus_samples_reg *reg = to_samples_reg(devattr);
	struct pmbus_data *data = i2c_get_clientdata(client);

	if (kstrtol(buf, 0, &val) < 0)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	ret = _pmbus_write_word_data(client, reg->page, reg->attr->reg, val);
	mutex_unlock(&data->update_lock);

	return ret ? : count;
}