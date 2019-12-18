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
struct sis5595_data {int /*<<< orphan*/  hwmon_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct sis5595_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sis5595_group ; 
 int /*<<< orphan*/  sis5595_group_in4 ; 
 int /*<<< orphan*/  sis5595_group_temp1 ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sis5595_remove(struct platform_device *pdev)
{
	struct sis5595_data *data = platform_get_drvdata(pdev);

	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_group(&pdev->dev.kobj, &sis5595_group);
	sysfs_remove_group(&pdev->dev.kobj, &sis5595_group_in4);
	sysfs_remove_group(&pdev->dev.kobj, &sis5595_group_temp1);

	return 0;
}