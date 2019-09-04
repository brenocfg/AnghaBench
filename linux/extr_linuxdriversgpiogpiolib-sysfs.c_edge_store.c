#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpiod_data {unsigned char irq_flags; int /*<<< orphan*/  mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {unsigned char flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 size_t EINVAL ; 
 struct gpiod_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpio_sysfs_free_irq (struct device*) ; 
 size_t gpio_sysfs_request_irq (struct device*,unsigned char) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sysfs_streq (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* trigger_types ; 

__attribute__((used)) static ssize_t edge_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct gpiod_data *data = dev_get_drvdata(dev);
	unsigned char flags;
	ssize_t	status = size;
	int i;

	for (i = 0; i < ARRAY_SIZE(trigger_types); i++) {
		if (sysfs_streq(trigger_types[i].name, buf))
			break;
	}

	if (i == ARRAY_SIZE(trigger_types))
		return -EINVAL;

	flags = trigger_types[i].flags;

	mutex_lock(&data->mutex);

	if (flags == data->irq_flags) {
		status = size;
		goto out_unlock;
	}

	if (data->irq_flags)
		gpio_sysfs_free_irq(dev);

	if (flags) {
		status = gpio_sysfs_request_irq(dev, flags);
		if (!status)
			status = size;
	}

out_unlock:
	mutex_unlock(&data->mutex);

	return status;
}