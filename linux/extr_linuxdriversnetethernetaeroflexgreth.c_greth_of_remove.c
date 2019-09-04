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
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;
struct net_device {scalar_t__ phydev; } ;
struct greth_private {int /*<<< orphan*/  regs; int /*<<< orphan*/  mdio; int /*<<< orphan*/  tx_bd_base_phys; int /*<<< orphan*/  tx_bd_base; int /*<<< orphan*/  rx_bd_base_phys; int /*<<< orphan*/  rx_bd_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct greth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  resource_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int greth_of_remove(struct platform_device *of_dev)
{
	struct net_device *ndev = platform_get_drvdata(of_dev);
	struct greth_private *greth = netdev_priv(ndev);

	/* Free descriptor areas */
	dma_free_coherent(&of_dev->dev, 1024, greth->rx_bd_base, greth->rx_bd_base_phys);

	dma_free_coherent(&of_dev->dev, 1024, greth->tx_bd_base, greth->tx_bd_base_phys);

	if (ndev->phydev)
		phy_stop(ndev->phydev);
	mdiobus_unregister(greth->mdio);

	unregister_netdev(ndev);
	free_netdev(ndev);

	of_iounmap(&of_dev->resource[0], greth->regs, resource_size(&of_dev->resource[0]));

	return 0;
}