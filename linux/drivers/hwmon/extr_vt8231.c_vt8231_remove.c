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
struct vt8231_data {int /*<<< orphan*/  hwmon_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct vt8231_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt8231_group ; 
 int /*<<< orphan*/ * vt8231_group_temps ; 
 int /*<<< orphan*/ * vt8231_group_volts ; 

__attribute__((used)) static int vt8231_remove(struct platform_device *pdev)
{
	struct vt8231_data *data = platform_get_drvdata(pdev);
	int i;

	hwmon_device_unregister(data->hwmon_dev);

	for (i = 0; i < ARRAY_SIZE(vt8231_group_volts); i++)
		sysfs_remove_group(&pdev->dev.kobj, &vt8231_group_volts[i]);

	for (i = 0; i < ARRAY_SIZE(vt8231_group_temps); i++)
		sysfs_remove_group(&pdev->dev.kobj, &vt8231_group_temps[i]);

	sysfs_remove_group(&pdev->dev.kobj, &vt8231_group);

	return 0;
}