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
struct TYPE_2__ {int enable; int /*<<< orphan*/  pwm; } ;
struct adm1026_data {int /*<<< orphan*/  update_lock; TYPE_1__ pwm1; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1026_REG_PWM ; 
 int /*<<< orphan*/  PWM_TO_REG (long) ; 
 int /*<<< orphan*/  adm1026_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adm1026_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t pwm1_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct adm1026_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;

	if (data->pwm1.enable == 1) {
		long val;
		int err;

		err = kstrtol(buf, 10, &val);
		if (err)
			return err;

		mutex_lock(&data->update_lock);
		data->pwm1.pwm = PWM_TO_REG(val);
		adm1026_write_value(client, ADM1026_REG_PWM, data->pwm1.pwm);
		mutex_unlock(&data->update_lock);
	}
	return count;
}