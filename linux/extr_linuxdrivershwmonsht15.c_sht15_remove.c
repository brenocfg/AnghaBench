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
struct sht15_data {int /*<<< orphan*/  read_lock; int /*<<< orphan*/  reg; int /*<<< orphan*/  nb; int /*<<< orphan*/  hwmon_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sht15_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sht15_attr_group ; 
 scalar_t__ sht15_soft_reset (struct sht15_data*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sht15_remove(struct platform_device *pdev)
{
	struct sht15_data *data = platform_get_drvdata(pdev);

	/*
	 * Make sure any reads from the device are done and
	 * prevent new ones beginning
	 */
	mutex_lock(&data->read_lock);
	if (sht15_soft_reset(data)) {
		mutex_unlock(&data->read_lock);
		return -EFAULT;
	}
	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_group(&pdev->dev.kobj, &sht15_attr_group);
	if (!IS_ERR(data->reg)) {
		regulator_unregister_notifier(data->reg, &data->nb);
		regulator_disable(data->reg);
	}

	mutex_unlock(&data->read_lock);

	return 0;
}