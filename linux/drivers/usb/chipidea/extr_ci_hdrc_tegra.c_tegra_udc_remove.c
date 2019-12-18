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
struct tegra_udc {int /*<<< orphan*/  clk; int /*<<< orphan*/  phy; int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_hdrc_remove_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct tegra_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_phy_set_suspend (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tegra_udc_remove(struct platform_device *pdev)
{
	struct tegra_udc *udc = platform_get_drvdata(pdev);

	ci_hdrc_remove_device(udc->dev);
	usb_phy_set_suspend(udc->phy, 1);
	clk_disable_unprepare(udc->clk);

	return 0;
}