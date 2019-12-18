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
struct cdns3 {int /*<<< orphan*/  usb3_phy; int /*<<< orphan*/  usb2_phy; int /*<<< orphan*/  role_sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns3_exit_roles (struct cdns3*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 struct cdns3* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_role_switch_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns3_remove(struct platform_device *pdev)
{
	struct cdns3 *cdns = platform_get_drvdata(pdev);

	pm_runtime_get_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	pm_runtime_put_noidle(&pdev->dev);
	cdns3_exit_roles(cdns);
	usb_role_switch_unregister(cdns->role_sw);
	phy_power_off(cdns->usb2_phy);
	phy_power_off(cdns->usb3_phy);
	phy_exit(cdns->usb2_phy);
	phy_exit(cdns->usb3_phy);
	return 0;
}