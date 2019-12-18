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
struct lm85_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp_min; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 scalar_t__ IS_ADT7468_OFF64 (struct lm85_data*) ; 
 int /*<<< orphan*/  LM85_REG_TEMP_MIN (int) ; 
 int /*<<< orphan*/  TEMP_TO_REG (long) ; 
 struct lm85_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  lm85_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_min_store(struct device *dev,
			      struct device_attribute *attr, const char *buf,
			      size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct lm85_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	if (IS_ADT7468_OFF64(data))
		val += 64;

	mutex_lock(&data->update_lock);
	data->temp_min[nr] = TEMP_TO_REG(val);
	lm85_write_value(client, LM85_REG_TEMP_MIN(nr), data->temp_min[nr]);
	mutex_unlock(&data->update_lock);
	return count;
}