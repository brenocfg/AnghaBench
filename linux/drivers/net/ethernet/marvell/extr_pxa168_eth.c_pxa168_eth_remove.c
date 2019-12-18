#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pxa168_eth_private {int /*<<< orphan*/  tx_timeout_task; int /*<<< orphan*/  smi_bus; scalar_t__ clk; int /*<<< orphan*/ * htpr; int /*<<< orphan*/  htpr_dma; TYPE_1__* dev; } ;
struct platform_device {int dummy; } ;
struct net_device {scalar_t__ phydev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ADDR_TABLE_SIZE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int pxa168_eth_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct pxa168_eth_private *pep = netdev_priv(dev);

	if (pep->htpr) {
		dma_free_coherent(pep->dev->dev.parent, HASH_ADDR_TABLE_SIZE,
				  pep->htpr, pep->htpr_dma);
		pep->htpr = NULL;
	}
	if (dev->phydev)
		phy_disconnect(dev->phydev);
	if (pep->clk) {
		clk_disable_unprepare(pep->clk);
	}

	mdiobus_unregister(pep->smi_bus);
	mdiobus_free(pep->smi_bus);
	unregister_netdev(dev);
	cancel_work_sync(&pep->tx_timeout_task);
	free_netdev(dev);
	return 0;
}