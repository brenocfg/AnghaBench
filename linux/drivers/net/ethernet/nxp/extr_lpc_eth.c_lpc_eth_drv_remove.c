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
struct netdata_local {scalar_t__ dma_buff_size; int /*<<< orphan*/  clk; int /*<<< orphan*/  mii_bus; int /*<<< orphan*/  net_base; int /*<<< orphan*/  dma_buff_base_p; int /*<<< orphan*/  dma_buff_base_v; TYPE_1__* pdev; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__ lpc32xx_return_iram (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct netdata_local* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  use_iram_for_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc_eth_drv_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct netdata_local *pldat = netdev_priv(ndev);

	unregister_netdev(ndev);

	if (!use_iram_for_net(&pldat->pdev->dev) ||
	    pldat->dma_buff_size > lpc32xx_return_iram(NULL, NULL))
		dma_free_coherent(&pldat->pdev->dev, pldat->dma_buff_size,
				  pldat->dma_buff_base_v,
				  pldat->dma_buff_base_p);
	free_irq(ndev->irq, ndev);
	iounmap(pldat->net_base);
	mdiobus_unregister(pldat->mii_bus);
	mdiobus_free(pldat->mii_bus);
	clk_disable_unprepare(pldat->clk);
	clk_put(pldat->clk);
	free_netdev(ndev);

	return 0;
}