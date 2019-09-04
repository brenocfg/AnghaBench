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
struct xgene_mac_ops {int /*<<< orphan*/  (* rx_enable ) (struct xgene_enet_pdata*) ;int /*<<< orphan*/  (* tx_enable ) (struct xgene_enet_pdata*) ;} ;
struct xgene_enet_pdata {int /*<<< orphan*/  link_work; int /*<<< orphan*/  rxq_cnt; int /*<<< orphan*/  txq_cnt; struct xgene_mac_ops* mac_ops; } ;
struct net_device {scalar_t__ phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_POLL_LINK_OFF ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (scalar_t__) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  stub2 (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_enet_napi_enable (struct xgene_enet_pdata*) ; 
 int xgene_enet_register_irq (struct net_device*) ; 

__attribute__((used)) static int xgene_enet_open(struct net_device *ndev)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	const struct xgene_mac_ops *mac_ops = pdata->mac_ops;
	int ret;

	ret = netif_set_real_num_tx_queues(ndev, pdata->txq_cnt);
	if (ret)
		return ret;

	ret = netif_set_real_num_rx_queues(ndev, pdata->rxq_cnt);
	if (ret)
		return ret;

	xgene_enet_napi_enable(pdata);
	ret = xgene_enet_register_irq(ndev);
	if (ret)
		return ret;

	if (ndev->phydev) {
		phy_start(ndev->phydev);
	} else {
		schedule_delayed_work(&pdata->link_work, PHY_POLL_LINK_OFF);
		netif_carrier_off(ndev);
	}

	mac_ops->tx_enable(pdata);
	mac_ops->rx_enable(pdata);
	netif_tx_start_all_queues(ndev);

	return ret;
}