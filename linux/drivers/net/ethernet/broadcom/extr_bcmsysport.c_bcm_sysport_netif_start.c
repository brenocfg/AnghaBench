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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  is_lite; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int INTRL2_0_RDMA_MBDONE ; 
 int INTRL2_0_TDMA_MBDONE_MASK ; 
 int INTRL2_0_TX_RING_FULL ; 
 int /*<<< orphan*/  bcm_sysport_dim_work ; 
 int /*<<< orphan*/  bcm_sysport_init_dim (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_sysport_init_rx_coalesce (struct bcm_sysport_priv*) ; 
 int /*<<< orphan*/  intrl2_0_mask_clear (struct bcm_sysport_priv*,int) ; 
 int /*<<< orphan*/  intrl2_1_mask_clear (struct bcm_sysport_priv*,int) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sysport_netif_start(struct net_device *dev)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);

	/* Enable NAPI */
	bcm_sysport_init_dim(priv, bcm_sysport_dim_work);
	bcm_sysport_init_rx_coalesce(priv);
	napi_enable(&priv->napi);

	/* Enable RX interrupt and TX ring full interrupt */
	intrl2_0_mask_clear(priv, INTRL2_0_RDMA_MBDONE | INTRL2_0_TX_RING_FULL);

	phy_start(dev->phydev);

	/* Enable TX interrupts for the TXQs */
	if (!priv->is_lite)
		intrl2_1_mask_clear(priv, 0xffffffff);
	else
		intrl2_0_mask_clear(priv, INTRL2_0_TDMA_MBDONE_MASK);
}