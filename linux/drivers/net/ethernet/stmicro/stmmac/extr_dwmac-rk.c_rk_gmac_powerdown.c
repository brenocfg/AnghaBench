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
struct rk_priv_data {scalar_t__ integrated_phy; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmac_clk_enable (struct rk_priv_data*,int) ; 
 int /*<<< orphan*/  phy_power_on (struct rk_priv_data*,int) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  rk_gmac_integrated_phy_powerdown (struct rk_priv_data*) ; 

__attribute__((used)) static void rk_gmac_powerdown(struct rk_priv_data *gmac)
{
	struct device *dev = &gmac->pdev->dev;

	if (gmac->integrated_phy)
		rk_gmac_integrated_phy_powerdown(gmac);

	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);

	phy_power_on(gmac, false);
	gmac_clk_enable(gmac, false);
}