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
struct gl518_data {int* fan_min; int beep_mask; int alarm_mask; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * fan_div; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int FAN_TO_REG (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL518_REG_ALARM ; 
 int /*<<< orphan*/  GL518_REG_FAN_LIMIT ; 
 struct gl518_data* dev_get_drvdata (struct device*) ; 
 void* gl518_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl518_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_min_store(struct device *dev,
			     struct device_attribute *attr, const char *buf,
			     size_t count)
{
	struct gl518_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int nr = to_sensor_dev_attr(attr)->index;
	int regvalue;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	regvalue = gl518_read_value(client, GL518_REG_FAN_LIMIT);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_div[nr]));
	regvalue = (regvalue & (0xff << (8 * nr)))
		 | (data->fan_min[nr] << (8 * (1 - nr)));
	gl518_write_value(client, GL518_REG_FAN_LIMIT, regvalue);

	data->beep_mask = gl518_read_value(client, GL518_REG_ALARM);
	if (data->fan_min[nr] == 0)
		data->alarm_mask &= ~(0x20 << nr);
	else
		data->alarm_mask |= (0x20 << nr);
	data->beep_mask &= data->alarm_mask;
	gl518_write_value(client, GL518_REG_ALARM, data->beep_mask);

	mutex_unlock(&data->update_lock);
	return count;
}