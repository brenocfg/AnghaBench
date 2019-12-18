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
struct f75375_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * pwm; int /*<<< orphan*/ * pwm_enable; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ auto_mode_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  duty_mode_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f75375_write_pwm (struct i2c_client*,int) ; 
 struct f75375_data* i2c_get_clientdata (struct i2c_client*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_pwm(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct f75375_data *data = i2c_get_clientdata(client);
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;

	if (auto_mode_enabled(data->pwm_enable[nr]) ||
	    !duty_mode_enabled(data->pwm_enable[nr]))
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm[nr] = clamp_val(val, 0, 255);
	f75375_write_pwm(client, nr);
	mutex_unlock(&data->update_lock);
	return count;
}