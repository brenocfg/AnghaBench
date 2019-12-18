#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct net_device {int dummy; } ;
struct fec_enet_private {int /*<<< orphan*/  phy_node; int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_ahb; scalar_t__ reg_phy; int /*<<< orphan*/  tx_timeout_work; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec_enet_mii_remove (struct fec_enet_private*) ; 
 int /*<<< orphan*/  fec_ptp_stop (struct platform_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int
fec_drv_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct device_node *np = pdev->dev.of_node;

	cancel_work_sync(&fep->tx_timeout_work);
	fec_ptp_stop(pdev);
	unregister_netdev(ndev);
	fec_enet_mii_remove(fep);
	if (fep->reg_phy)
		regulator_disable(fep->reg_phy);
	pm_runtime_put(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(fep->clk_ahb);
	clk_disable_unprepare(fep->clk_ipg);
	if (of_phy_is_fixed_link(np))
		of_phy_deregister_fixed_link(np);
	of_node_put(fep->phy_node);
	free_netdev(ndev);

	return 0;
}