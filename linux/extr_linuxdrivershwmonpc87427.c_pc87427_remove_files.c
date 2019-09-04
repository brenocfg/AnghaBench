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
struct pc87427_data {int fan_enabled; int pwm_enabled; int temp_enabled; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_name ; 
 struct pc87427_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pc87427_group_fan ; 
 int /*<<< orphan*/ * pc87427_group_pwm ; 
 int /*<<< orphan*/ * pc87427_group_temp ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pc87427_remove_files(struct device *dev)
{
	struct pc87427_data *data = dev_get_drvdata(dev);
	int i;

	device_remove_file(dev, &dev_attr_name);
	for (i = 0; i < 8; i++) {
		if (!(data->fan_enabled & (1 << i)))
			continue;
		sysfs_remove_group(&dev->kobj, &pc87427_group_fan[i]);
	}
	for (i = 0; i < 4; i++) {
		if (!(data->pwm_enabled & (1 << i)))
			continue;
		sysfs_remove_group(&dev->kobj, &pc87427_group_pwm[i]);
	}
	for (i = 0; i < 6; i++) {
		if (!(data->temp_enabled & (1 << i)))
			continue;
		sysfs_remove_group(&dev->kobj, &pc87427_group_temp[i]);
	}
}