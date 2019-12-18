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
struct platform_device {int dummy; } ;
struct dwc2_hsotg {int /*<<< orphan*/  supplies; scalar_t__ clk; int /*<<< orphan*/  phy; TYPE_1__* plat; scalar_t__ uphy; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* phy_exit ) (struct platform_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  phy_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int phy_exit (int /*<<< orphan*/ ) ; 
 int phy_power_off (int /*<<< orphan*/ ) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_phy_shutdown (scalar_t__) ; 

__attribute__((used)) static int __dwc2_lowlevel_hw_disable(struct dwc2_hsotg *hsotg)
{
	struct platform_device *pdev = to_platform_device(hsotg->dev);
	int ret = 0;

	if (hsotg->uphy) {
		usb_phy_shutdown(hsotg->uphy);
	} else if (hsotg->plat && hsotg->plat->phy_exit) {
		ret = hsotg->plat->phy_exit(pdev, hsotg->plat->phy_type);
	} else {
		ret = phy_exit(hsotg->phy);
		if (ret == 0)
			ret = phy_power_off(hsotg->phy);
	}
	if (ret)
		return ret;

	if (hsotg->clk)
		clk_disable_unprepare(hsotg->clk);

	ret = regulator_bulk_disable(ARRAY_SIZE(hsotg->supplies),
				     hsotg->supplies);

	return ret;
}