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
struct xgene_mac_ops {int /*<<< orphan*/  (* rx_disable ) (struct xgene_enet_pdata*) ;int /*<<< orphan*/  (* tx_disable ) (struct xgene_enet_pdata*) ;} ;
struct xgene_enet_pdata {int rxq_cnt; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  link_work; struct xgene_mac_ops* mac_ops; } ;
struct net_device {scalar_t__ phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  stub2 (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_enet_free_irq (struct net_device*) ; 
 int /*<<< orphan*/  xgene_enet_napi_disable (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_enet_process_ring (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xgene_enet_close(struct net_device *ndev)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	const struct xgene_mac_ops *mac_ops = pdata->mac_ops;
	int i;

	netif_tx_stop_all_queues(ndev);
	mac_ops->tx_disable(pdata);
	mac_ops->rx_disable(pdata);

	if (ndev->phydev)
		phy_stop(ndev->phydev);
	else
		cancel_delayed_work_sync(&pdata->link_work);

	xgene_enet_free_irq(ndev);
	xgene_enet_napi_disable(pdata);
	for (i = 0; i < pdata->rxq_cnt; i++)
		xgene_enet_process_ring(pdata->rx_ring[i], -1);

	return 0;
}