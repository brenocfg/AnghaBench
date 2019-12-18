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
struct gl520_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp_max_hyst; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/ * GL520_REG_TEMP_MAX_HYST ; 
 int /*<<< orphan*/  TEMP_TO_REG (long) ; 
 struct gl520_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gl520_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_max_hyst_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct gl520_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int n = to_sensor_dev_attr(attr)->index;
	long v;
	int err;

	err = kstrtol(buf, 10, &v);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->temp_max_hyst[n] = TEMP_TO_REG(v);
	gl520_write_value(client, GL520_REG_TEMP_MAX_HYST[n],
			  data->temp_max_hyst[n]);
	mutex_unlock(&data->update_lock);
	return count;
}