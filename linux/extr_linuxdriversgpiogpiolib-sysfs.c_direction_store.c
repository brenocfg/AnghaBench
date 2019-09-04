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
struct gpiod_data {int /*<<< orphan*/  mutex; struct gpio_desc* desc; } ;
struct gpio_desc {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct gpiod_data* dev_get_drvdata (struct device*) ; 
 int gpiod_direction_input (struct gpio_desc*) ; 
 int gpiod_direction_output_raw (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 

__attribute__((used)) static ssize_t direction_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct gpiod_data *data = dev_get_drvdata(dev);
	struct gpio_desc *desc = data->desc;
	ssize_t			status;

	mutex_lock(&data->mutex);

	if (sysfs_streq(buf, "high"))
		status = gpiod_direction_output_raw(desc, 1);
	else if (sysfs_streq(buf, "out") || sysfs_streq(buf, "low"))
		status = gpiod_direction_output_raw(desc, 0);
	else if (sysfs_streq(buf, "in"))
		status = gpiod_direction_input(desc);
	else
		status = -EINVAL;

	mutex_unlock(&data->mutex);

	return status ? : size;
}