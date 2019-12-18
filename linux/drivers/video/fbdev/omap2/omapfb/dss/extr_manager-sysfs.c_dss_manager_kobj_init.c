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
struct omap_overlay_manager {int /*<<< orphan*/  id; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_ktype ; 

int dss_manager_kobj_init(struct omap_overlay_manager *mgr,
		struct platform_device *pdev)
{
	return kobject_init_and_add(&mgr->kobj, &manager_ktype,
			&pdev->dev.kobj, "manager%d", mgr->id);
}