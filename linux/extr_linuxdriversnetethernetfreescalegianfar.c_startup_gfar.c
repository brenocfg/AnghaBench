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
struct gfar_private {int oldduplex; scalar_t__ oldspeed; scalar_t__ oldlink; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFAR_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_napi (struct gfar_private*) ; 
 int gfar_alloc_skb_resources (struct net_device*) ; 
 int /*<<< orphan*/  gfar_init_tx_rx_base (struct gfar_private*) ; 
 int /*<<< orphan*/  gfar_mac_reset (struct gfar_private*) ; 
 int /*<<< orphan*/  gfar_start (struct gfar_private*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

int startup_gfar(struct net_device *ndev)
{
	struct gfar_private *priv = netdev_priv(ndev);
	int err;

	gfar_mac_reset(priv);

	err = gfar_alloc_skb_resources(ndev);
	if (err)
		return err;

	gfar_init_tx_rx_base(priv);

	smp_mb__before_atomic();
	clear_bit(GFAR_DOWN, &priv->state);
	smp_mb__after_atomic();

	/* Start Rx/Tx DMA and enable the interrupts */
	gfar_start(priv);

	/* force link state update after mac reset */
	priv->oldlink = 0;
	priv->oldspeed = 0;
	priv->oldduplex = -1;

	phy_start(ndev->phydev);

	enable_napi(priv);

	netif_tx_wake_all_queues(ndev);

	return 0;
}