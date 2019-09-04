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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;
struct abx500_temp {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  abx500_temp_group ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct abx500_temp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int abx500_temp_remove(struct platform_device *pdev)
{
	struct abx500_temp *data = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&data->work);
	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_group(&pdev->dev.kobj, &abx500_temp_group);

	return 0;
}