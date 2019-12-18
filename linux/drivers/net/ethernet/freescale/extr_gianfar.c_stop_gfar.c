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
struct gfar_private {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFAR_DOWN ; 
 int /*<<< orphan*/  disable_napi (struct gfar_private*) ; 
 int /*<<< orphan*/  free_skb_resources (struct gfar_private*) ; 
 int /*<<< orphan*/  gfar_halt (struct gfar_private*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

void stop_gfar(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);

	netif_tx_stop_all_queues(dev);

	smp_mb__before_atomic();
	set_bit(GFAR_DOWN, &priv->state);
	smp_mb__after_atomic();

	disable_napi(priv);

	/* disable ints and gracefully shut down Rx/Tx DMA */
	gfar_halt(priv);

	phy_stop(dev->phydev);

	free_skb_resources(priv);
}