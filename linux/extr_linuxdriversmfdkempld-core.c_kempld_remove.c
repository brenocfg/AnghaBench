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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct kempld_platform_data {int /*<<< orphan*/  (* release_hardware_mutex ) (struct kempld_device_data*) ;} ;
struct kempld_device_data {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 struct kempld_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 struct kempld_device_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pld_attr_group ; 
 int /*<<< orphan*/  stub1 (struct kempld_device_data*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kempld_remove(struct platform_device *pdev)
{
	struct kempld_device_data *pld = platform_get_drvdata(pdev);
	const struct kempld_platform_data *pdata = dev_get_platdata(pld->dev);

	sysfs_remove_group(&pld->dev->kobj, &pld_attr_group);

	mfd_remove_devices(&pdev->dev);
	pdata->release_hardware_mutex(pld);

	return 0;
}