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
struct net_device {int dummy; } ;
struct bcmgenet_priv {int /*<<< orphan*/ * tx_rings; TYPE_1__* hw_params; } ;
struct TYPE_2__ {int tx_queues; } ;

/* Variables and functions */
 size_t DESC_INDEX ; 
 int /*<<< orphan*/  bcmgenet_tx_reclaim (struct net_device*,int /*<<< orphan*/ *) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_is_multiqueue (struct net_device*) ; 

__attribute__((used)) static void bcmgenet_tx_reclaim_all(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	int i;

	if (netif_is_multiqueue(dev)) {
		for (i = 0; i < priv->hw_params->tx_queues; i++)
			bcmgenet_tx_reclaim(dev, &priv->tx_rings[i]);
	}

	bcmgenet_tx_reclaim(dev, &priv->tx_rings[DESC_INDEX]);
}