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
struct ti_st_plat_data {int /*<<< orphan*/  nshutdown_gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; struct ti_st_plat_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct kim_data_s {int /*<<< orphan*/  core_data; int /*<<< orphan*/ * kim_pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kim_data_s*) ; 
 int /*<<< orphan*/  kim_debugfs_dir ; 
 struct kim_data_s* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  st_core_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uim_attr_grp ; 

__attribute__((used)) static int kim_remove(struct platform_device *pdev)
{
	/* free the GPIOs requested */
	struct ti_st_plat_data	*pdata = pdev->dev.platform_data;
	struct kim_data_s	*kim_gdata;

	kim_gdata = platform_get_drvdata(pdev);

	/* Free the Bluetooth/FM/GPIO
	 * nShutdown gpio from the system
	 */
	gpio_free(pdata->nshutdown_gpio);
	pr_info("nshutdown GPIO Freed");

	debugfs_remove_recursive(kim_debugfs_dir);
	sysfs_remove_group(&pdev->dev.kobj, &uim_attr_grp);
	pr_info("sysfs entries removed");

	kim_gdata->kim_pdev = NULL;
	st_core_exit(kim_gdata->core_data);

	kfree(kim_gdata);
	kim_gdata = NULL;
	return 0;
}