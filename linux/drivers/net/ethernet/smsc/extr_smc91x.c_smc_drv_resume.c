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
struct smc_local {scalar_t__ phy_type; int /*<<< orphan*/  phy_configure; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct smc_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  smc_enable (struct net_device*) ; 
 int /*<<< orphan*/  smc_enable_device (struct platform_device*) ; 
 int /*<<< orphan*/  smc_phy_configure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_reset (struct net_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int smc_drv_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct net_device *ndev = platform_get_drvdata(pdev);

	if (ndev) {
		struct smc_local *lp = netdev_priv(ndev);
		smc_enable_device(pdev);
		if (netif_running(ndev)) {
			smc_reset(ndev);
			smc_enable(ndev);
			if (lp->phy_type != 0)
				smc_phy_configure(&lp->phy_configure);
			netif_device_attach(ndev);
		}
	}
	return 0;
}