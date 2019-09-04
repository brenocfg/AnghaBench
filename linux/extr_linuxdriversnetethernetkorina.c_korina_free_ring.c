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
struct net_device {int dummy; } ;
struct korina_private {int /*<<< orphan*/ ** tx_skb; TYPE_2__* td_ring; int /*<<< orphan*/ ** rx_skb; TYPE_1__* rd_ring; } ;
struct TYPE_4__ {scalar_t__ control; } ;
struct TYPE_3__ {scalar_t__ control; } ;

/* Variables and functions */
 int KORINA_NUM_RDS ; 
 int KORINA_NUM_TDS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 struct korina_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void korina_free_ring(struct net_device *dev)
{
	struct korina_private *lp = netdev_priv(dev);
	int i;

	for (i = 0; i < KORINA_NUM_RDS; i++) {
		lp->rd_ring[i].control = 0;
		if (lp->rx_skb[i])
			dev_kfree_skb_any(lp->rx_skb[i]);
		lp->rx_skb[i] = NULL;
	}

	for (i = 0; i < KORINA_NUM_TDS; i++) {
		lp->td_ring[i].control = 0;
		if (lp->tx_skb[i])
			dev_kfree_skb_any(lp->tx_skb[i]);
		lp->tx_skb[i] = NULL;
	}
}