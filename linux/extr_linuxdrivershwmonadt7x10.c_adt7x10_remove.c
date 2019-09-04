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
struct device {int /*<<< orphan*/  kobj; } ;
struct adt7x10_data {scalar_t__ oldconfig; scalar_t__ config; scalar_t__ name; int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7X10_CONFIG ; 
 int /*<<< orphan*/  adt7x10_group ; 
 int /*<<< orphan*/  adt7x10_write_byte (struct device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_attr_name ; 
 struct adt7x10_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct device*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int adt7x10_remove(struct device *dev, int irq)
{
	struct adt7x10_data *data = dev_get_drvdata(dev);

	if (irq > 0)
		free_irq(irq, dev);

	hwmon_device_unregister(data->hwmon_dev);
	if (data->name)
		device_remove_file(dev, &dev_attr_name);
	sysfs_remove_group(&dev->kobj, &adt7x10_group);
	if (data->oldconfig != data->config)
		adt7x10_write_byte(dev, ADT7X10_CONFIG, data->oldconfig);
	return 0;
}