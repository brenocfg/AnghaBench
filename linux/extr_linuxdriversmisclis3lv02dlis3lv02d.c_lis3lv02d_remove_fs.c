#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lis3lv02d {int /*<<< orphan*/  reg_cache; scalar_t__ pm_dev; TYPE_2__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lis3lv02d_attribute_group ; 
 int /*<<< orphan*/  lis3lv02d_poweroff (struct lis3lv02d*) ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_barrier (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_disable (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_suspended (scalar_t__) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int lis3lv02d_remove_fs(struct lis3lv02d *lis3)
{
	sysfs_remove_group(&lis3->pdev->dev.kobj, &lis3lv02d_attribute_group);
	platform_device_unregister(lis3->pdev);
	if (lis3->pm_dev) {
		/* Barrier after the sysfs remove */
		pm_runtime_barrier(lis3->pm_dev);

		/* SYSFS may have left chip running. Turn off if necessary */
		if (!pm_runtime_suspended(lis3->pm_dev))
			lis3lv02d_poweroff(lis3);

		pm_runtime_disable(lis3->pm_dev);
		pm_runtime_set_suspended(lis3->pm_dev);
	}
	kfree(lis3->reg_cache);
	return 0;
}