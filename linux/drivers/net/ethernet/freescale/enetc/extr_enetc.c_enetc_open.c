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
struct enetc_ndev_priv {int bdr_int_num; TYPE_1__** int_vector; int /*<<< orphan*/  num_rx_rings; int /*<<< orphan*/  num_tx_rings; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int enetc_alloc_rx_resources (struct enetc_ndev_priv*) ; 
 int enetc_alloc_tx_resources (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_enable_interrupts (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_free_irqs (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_free_rx_resources (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_free_tx_resources (struct enetc_ndev_priv*) ; 
 int enetc_phy_connect (struct net_device*) ; 
 int /*<<< orphan*/  enetc_setup_bdrs (struct enetc_ndev_priv*) ; 
 int enetc_setup_irqs (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  phy_start (scalar_t__) ; 

int enetc_open(struct net_device *ndev)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	int i, err;

	err = enetc_setup_irqs(priv);
	if (err)
		return err;

	err = enetc_phy_connect(ndev);
	if (err)
		goto err_phy_connect;

	err = enetc_alloc_tx_resources(priv);
	if (err)
		goto err_alloc_tx;

	err = enetc_alloc_rx_resources(priv);
	if (err)
		goto err_alloc_rx;

	enetc_setup_bdrs(priv);

	err = netif_set_real_num_tx_queues(ndev, priv->num_tx_rings);
	if (err)
		goto err_set_queues;

	err = netif_set_real_num_rx_queues(ndev, priv->num_rx_rings);
	if (err)
		goto err_set_queues;

	for (i = 0; i < priv->bdr_int_num; i++)
		napi_enable(&priv->int_vector[i]->napi);

	enetc_enable_interrupts(priv);

	if (ndev->phydev)
		phy_start(ndev->phydev);
	else
		netif_carrier_on(ndev);

	netif_tx_start_all_queues(ndev);

	return 0;

err_set_queues:
	enetc_free_rx_resources(priv);
err_alloc_rx:
	enetc_free_tx_resources(priv);
err_alloc_tx:
	if (ndev->phydev)
		phy_disconnect(ndev->phydev);
err_phy_connect:
	enetc_free_irqs(priv);

	return err;
}