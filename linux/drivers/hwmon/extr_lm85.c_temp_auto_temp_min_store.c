#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lm85_data {int* pwm_freq; int /*<<< orphan*/  update_lock; TYPE_1__* zone; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int index; } ;
struct TYPE_3__ {int limit; int range; int max_desired; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM85_REG_AFAN_LIMIT (int) ; 
 int /*<<< orphan*/  LM85_REG_AFAN_RANGE (int) ; 
 int RANGE_TO_REG (scalar_t__) ; 
 scalar_t__ TEMP_FROM_REG (int) ; 
 int TEMP_TO_REG (long) ; 
 struct lm85_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  lm85_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_auto_temp_min_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct lm85_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->zone[nr].limit = TEMP_TO_REG(val);
	lm85_write_value(client, LM85_REG_AFAN_LIMIT(nr),
		data->zone[nr].limit);

/* Update temp_auto_max and temp_auto_range */
	data->zone[nr].range = RANGE_TO_REG(
		TEMP_FROM_REG(data->zone[nr].max_desired) -
		TEMP_FROM_REG(data->zone[nr].limit));
	lm85_write_value(client, LM85_REG_AFAN_RANGE(nr),
		((data->zone[nr].range & 0x0f) << 4)
		| data->pwm_freq[nr]);

	mutex_unlock(&data->update_lock);
	return count;
}