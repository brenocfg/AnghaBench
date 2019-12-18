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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ci_hdrc {scalar_t__ supports_runtime_pm; scalar_t__ role_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_hdrc_enter_lpm (struct ci_hdrc*,int) ; 
 int /*<<< orphan*/  ci_role_destroy (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ci_ulpi_exit (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ci_usb_phy_exit (struct ci_hdrc*) ; 
 int /*<<< orphan*/  dbg_remove_files (struct ci_hdrc*) ; 
 struct ci_hdrc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_role_switch_unregister (scalar_t__) ; 

__attribute__((used)) static int ci_hdrc_remove(struct platform_device *pdev)
{
	struct ci_hdrc *ci = platform_get_drvdata(pdev);

	if (ci->role_switch)
		usb_role_switch_unregister(ci->role_switch);

	if (ci->supports_runtime_pm) {
		pm_runtime_get_sync(&pdev->dev);
		pm_runtime_disable(&pdev->dev);
		pm_runtime_put_noidle(&pdev->dev);
	}

	dbg_remove_files(ci);
	ci_role_destroy(ci);
	ci_hdrc_enter_lpm(ci, true);
	ci_usb_phy_exit(ci);
	ci_ulpi_exit(ci);

	return 0;
}