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
struct gpiod_data {int /*<<< orphan*/  mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 struct gpiod_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ gpio_sysfs_set_active_low (struct device*,long) ; 
 scalar_t__ kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t active_low_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct gpiod_data	*data = dev_get_drvdata(dev);
	ssize_t			status;
	long			value;

	mutex_lock(&data->mutex);

	status = kstrtol(buf, 0, &value);
	if (status == 0)
		status = gpio_sysfs_set_active_low(dev, value);

	mutex_unlock(&data->mutex);

	return status ? : size;
}