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
struct net_device {scalar_t__ phydev; } ;
struct enetc_ndev_priv {int bdr_int_num; TYPE_1__** int_vector; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  enetc_clear_bdrs (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_disable_interrupts (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_free_irqs (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_free_rx_resources (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_free_rxtx_rings (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_free_tx_resources (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 

int enetc_close(struct net_device *ndev)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	int i;

	netif_tx_stop_all_queues(ndev);

	if (ndev->phydev) {
		phy_stop(ndev->phydev);
		phy_disconnect(ndev->phydev);
	} else {
		netif_carrier_off(ndev);
	}

	for (i = 0; i < priv->bdr_int_num; i++) {
		napi_synchronize(&priv->int_vector[i]->napi);
		napi_disable(&priv->int_vector[i]->napi);
	}

	enetc_disable_interrupts(priv);
	enetc_clear_bdrs(priv);

	enetc_free_rxtx_rings(priv);
	enetc_free_rx_resources(priv);
	enetc_free_tx_resources(priv);
	enetc_free_irqs(priv);

	return 0;
}