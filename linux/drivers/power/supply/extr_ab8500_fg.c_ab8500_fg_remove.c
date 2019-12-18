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
struct platform_device {int dummy; } ;
struct ab8500_fg {int /*<<< orphan*/  fg_psy; int /*<<< orphan*/  fg_wq; int /*<<< orphan*/  dev; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int ab8500_fg_coulomb_counter (struct ab8500_fg*,int) ; 
 int /*<<< orphan*/  ab8500_fg_sysfs_exit (struct ab8500_fg*) ; 
 int /*<<< orphan*/  ab8500_fg_sysfs_psy_remove_attrs (struct ab8500_fg*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct ab8500_fg* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_fg_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct ab8500_fg *di = platform_get_drvdata(pdev);

	list_del(&di->node);

	/* Disable coulomb counter */
	ret = ab8500_fg_coulomb_counter(di, false);
	if (ret)
		dev_err(di->dev, "failed to disable coulomb counter\n");

	destroy_workqueue(di->fg_wq);
	ab8500_fg_sysfs_exit(di);

	flush_scheduled_work();
	ab8500_fg_sysfs_psy_remove_attrs(di);
	power_supply_unregister(di->fg_psy);
	return ret;
}