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
struct dm816x_usb_phy {int /*<<< orphan*/  refclk; int /*<<< orphan*/  dev; int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct dm816x_usb_phy* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm816x_usb_phy_remove(struct platform_device *pdev)
{
	struct dm816x_usb_phy *phy = platform_get_drvdata(pdev);

	usb_remove_phy(&phy->phy);
	pm_runtime_disable(phy->dev);
	clk_unprepare(phy->refclk);

	return 0;
}