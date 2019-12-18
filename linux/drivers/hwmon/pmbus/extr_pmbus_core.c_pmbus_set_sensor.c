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
typedef  int /*<<< orphan*/  u16 ;
struct pmbus_sensor {int /*<<< orphan*/  data; int /*<<< orphan*/  reg; int /*<<< orphan*/  page; } ;
struct pmbus_data {int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int _pmbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pmbus_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmbus_data2reg (struct pmbus_data*,struct pmbus_sensor*,long) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 struct pmbus_sensor* to_pmbus_sensor (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pmbus_set_sensor(struct device *dev,
				struct device_attribute *devattr,
				const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev->parent);
	struct pmbus_data *data = i2c_get_clientdata(client);
	struct pmbus_sensor *sensor = to_pmbus_sensor(devattr);
	ssize_t rv = count;
	long val = 0;
	int ret;
	u16 regval;

	if (kstrtol(buf, 10, &val) < 0)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	regval = pmbus_data2reg(data, sensor, val);
	ret = _pmbus_write_word_data(client, sensor->page, sensor->reg, regval);
	if (ret < 0)
		rv = ret;
	else
		sensor->data = regval;
	mutex_unlock(&data->update_lock);
	return rv;
}