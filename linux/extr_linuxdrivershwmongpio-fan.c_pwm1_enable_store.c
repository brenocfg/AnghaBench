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
struct gpio_fan_data {unsigned long pwm_enable; int /*<<< orphan*/  lock; scalar_t__ num_speed; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct gpio_fan_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_fan_speed (struct gpio_fan_data*,scalar_t__) ; 

__attribute__((used)) static ssize_t pwm1_enable_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct gpio_fan_data *fan_data = dev_get_drvdata(dev);
	unsigned long val;

	if (kstrtoul(buf, 10, &val) || val > 1)
		return -EINVAL;

	if (fan_data->pwm_enable == val)
		return count;

	mutex_lock(&fan_data->lock);

	fan_data->pwm_enable = val;

	/* Disable manual control mode: set fan at full speed. */
	if (val == 0)
		set_fan_speed(fan_data, fan_data->num_speed - 1);

	mutex_unlock(&fan_data->lock);

	return count;
}