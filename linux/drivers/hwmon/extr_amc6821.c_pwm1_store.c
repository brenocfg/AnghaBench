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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct amc6821_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  pwm1; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMC6821_REG_DCY ; 
 int /*<<< orphan*/  clamp_val (long,int /*<<< orphan*/ ,int) ; 
 struct amc6821_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t pwm1_store(struct device *dev,
			  struct device_attribute *devattr, const char *buf,
			  size_t count)
{
	struct amc6821_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int ret = kstrtol(buf, 10, &val);
	if (ret)
		return ret;

	mutex_lock(&data->update_lock);
	data->pwm1 = clamp_val(val , 0, 255);
	i2c_smbus_write_byte_data(client, AMC6821_REG_DCY, data->pwm1);
	mutex_unlock(&data->update_lock);
	return count;
}