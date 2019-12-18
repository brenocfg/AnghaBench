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
struct omap_overlay_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int dss_manager_kobj_init (struct omap_overlay_manager*,struct platform_device*) ; 
 struct omap_overlay_manager* managers ; 
 int num_managers ; 

int dss_init_overlay_managers_sysfs(struct platform_device *pdev)
{
	int i, r;

	for (i = 0; i < num_managers; ++i) {
		struct omap_overlay_manager *mgr = &managers[i];

		r = dss_manager_kobj_init(mgr, pdev);
		if (r)
			DSSERR("failed to create sysfs file\n");
	}

	return 0;
}