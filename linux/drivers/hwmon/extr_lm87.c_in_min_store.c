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
struct lm87_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * in_min; int /*<<< orphan*/ * in_scale; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_TO_REG (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM87_REG_AIN_MIN (int) ; 
 int /*<<< orphan*/  LM87_REG_IN_MIN (int) ; 
 struct i2c_client* dev_get_drvdata (struct device*) ; 
 struct lm87_data* i2c_get_clientdata (struct i2c_client*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  lm87_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t in_min_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct i2c_client *client = dev_get_drvdata(dev);
	struct lm87_data *data = i2c_get_clientdata(client);
	int nr = to_sensor_dev_attr(attr)->index;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = IN_TO_REG(val, data->in_scale[nr]);
	lm87_write_value(client, nr < 6 ? LM87_REG_IN_MIN(nr) :
			 LM87_REG_AIN_MIN(nr - 6), data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	return count;
}