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

/* Variables and functions */
 int /*<<< orphan*/  compat_init_lock ; 
 scalar_t__ compat_refcnt ; 
 int /*<<< orphan*/  display_uninit_sysfs (struct platform_device*) ; 
 int /*<<< orphan*/  dss_dispc_uninitialize_irq () ; 
 struct platform_device* dss_get_core_pdev () ; 
 int /*<<< orphan*/  dss_uninit_overlay_managers_sysfs (struct platform_device*) ; 
 int /*<<< orphan*/  dss_uninit_overlays (struct platform_device*) ; 
 int /*<<< orphan*/  dss_uninstall_mgr_ops () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void omapdss_compat_uninit(void)
{
	struct platform_device *pdev = dss_get_core_pdev();

	mutex_lock(&compat_init_lock);

	if (--compat_refcnt > 0)
		goto out;

	dss_dispc_uninitialize_irq();

	display_uninit_sysfs(pdev);

	dss_uninstall_mgr_ops();

	dss_uninit_overlay_managers_sysfs(pdev);
	dss_uninit_overlays(pdev);
out:
	mutex_unlock(&compat_init_lock);
}