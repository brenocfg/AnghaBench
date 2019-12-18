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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct amc6821_data {int* fan; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 size_t EIO ; 
 scalar_t__ clamp_val (long,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct amc6821_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * fan_reg_hi ; 
 int /*<<< orphan*/ * fan_reg_low ; 
 scalar_t__ i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_store(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct amc6821_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int ix = to_sensor_dev_attr(attr)->index;
	int ret = kstrtol(buf, 10, &val);
	if (ret)
		return ret;
	val = 1 > val ? 0xFFFF : 6000000/val;

	mutex_lock(&data->update_lock);
	data->fan[ix] = (u16) clamp_val(val, 1, 0xFFFF);
	if (i2c_smbus_write_byte_data(client, fan_reg_low[ix],
			data->fan[ix] & 0xFF)) {
		dev_err(&client->dev, "Register write error, aborting.\n");
		count = -EIO;
		goto EXIT;
	}
	if (i2c_smbus_write_byte_data(client,
			fan_reg_hi[ix], data->fan[ix] >> 8)) {
		dev_err(&client->dev, "Register write error, aborting.\n");
		count = -EIO;
	}
EXIT:
	mutex_unlock(&data->update_lock);
	return count;
}