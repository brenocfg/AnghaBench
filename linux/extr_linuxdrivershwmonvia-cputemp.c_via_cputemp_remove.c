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
struct via_cputemp_data {scalar_t__ vrm; int /*<<< orphan*/  hwmon_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_cpu0_vid ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct via_cputemp_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  via_cputemp_group ; 

__attribute__((used)) static int via_cputemp_remove(struct platform_device *pdev)
{
	struct via_cputemp_data *data = platform_get_drvdata(pdev);

	hwmon_device_unregister(data->hwmon_dev);
	if (data->vrm)
		device_remove_file(&pdev->dev, &dev_attr_cpu0_vid);
	sysfs_remove_group(&pdev->dev.kobj, &via_cputemp_group);
	return 0;
}