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
struct net_device {int dummy; } ;
struct ethtool_ringparam {int rx_max_pending; int tx_max_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; } ;
struct bcm_enet_priv {int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; } ;

/* Variables and functions */
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bcm_enetsw_get_ringparam(struct net_device *dev,
				     struct ethtool_ringparam *ering)
{
	struct bcm_enet_priv *priv;

	priv = netdev_priv(dev);

	/* rx/tx ring is actually only limited by memory */
	ering->rx_max_pending = 8192;
	ering->tx_max_pending = 8192;
	ering->rx_mini_max_pending = 0;
	ering->rx_jumbo_max_pending = 0;
	ering->rx_pending = priv->rx_ring_size;
	ering->tx_pending = priv->tx_ring_size;
}