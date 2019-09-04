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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct net_device {int /*<<< orphan*/ * phydev; } ;
struct macb {int /*<<< orphan*/  phy_node; int /*<<< orphan*/  rx_clk; int /*<<< orphan*/  pclk; int /*<<< orphan*/  hclk; int /*<<< orphan*/  tx_clk; int /*<<< orphan*/  mii_bus; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct macb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int macb_remove(struct platform_device *pdev)
{
	struct net_device *dev;
	struct macb *bp;
	struct device_node *np = pdev->dev.of_node;

	dev = platform_get_drvdata(pdev);

	if (dev) {
		bp = netdev_priv(dev);
		if (dev->phydev)
			phy_disconnect(dev->phydev);
		mdiobus_unregister(bp->mii_bus);
		if (np && of_phy_is_fixed_link(np))
			of_phy_deregister_fixed_link(np);
		dev->phydev = NULL;
		mdiobus_free(bp->mii_bus);

		unregister_netdev(dev);
		clk_disable_unprepare(bp->tx_clk);
		clk_disable_unprepare(bp->hclk);
		clk_disable_unprepare(bp->pclk);
		clk_disable_unprepare(bp->rx_clk);
		of_node_put(bp->phy_node);
		free_netdev(dev);
	}

	return 0;
}