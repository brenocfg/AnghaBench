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
struct adm1031_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp_max; struct i2c_client* client; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1031_REG_TEMP_MAX (int) ; 
 int /*<<< orphan*/  TEMP_TO_REG (long) ; 
 int /*<<< orphan*/  adm1031_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long clamp_val (long,int,int) ; 
 struct adm1031_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_max_store(struct device *dev,
			      struct device_attribute *attr, const char *buf,
			      size_t count)
{
	struct adm1031_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int nr = to_sensor_dev_attr(attr)->index;
	long val;
	int ret;

	ret = kstrtol(buf, 10, &val);
	if (ret)
		return ret;

	val = clamp_val(val, -55000, 127000);
	mutex_lock(&data->update_lock);
	data->temp_max[nr] = TEMP_TO_REG(val);
	adm1031_write_value(client, ADM1031_REG_TEMP_MAX(nr),
			    data->temp_max[nr]);
	mutex_unlock(&data->update_lock);
	return count;
}