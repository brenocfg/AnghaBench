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
struct pc87427_data {int pwm_auto_ok; int /*<<< orphan*/  lock; int /*<<< orphan*/ * pwm; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 size_t EINVAL ; 
 struct pc87427_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc87427_readall_pwm (struct pc87427_data*,int) ; 
 int /*<<< orphan*/  pwm_enable_to_reg (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 int /*<<< orphan*/  update_pwm_enable (struct pc87427_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pwm_enable_store(struct device *dev,
				struct device_attribute *devattr,
				const char *buf, size_t count)
{
	struct pc87427_data *data = dev_get_drvdata(dev);
	int nr = to_sensor_dev_attr(devattr)->index;
	unsigned long val;

	if (kstrtoul(buf, 10, &val) < 0 || val > 2)
		return -EINVAL;
	/* Can't go to automatic mode if it isn't configured */
	if (val == 2 && !(data->pwm_auto_ok & (1 << nr)))
		return -EINVAL;

	mutex_lock(&data->lock);
	pc87427_readall_pwm(data, nr);
	update_pwm_enable(data, nr, pwm_enable_to_reg(val, data->pwm[nr]));
	mutex_unlock(&data->lock);

	return count;
}