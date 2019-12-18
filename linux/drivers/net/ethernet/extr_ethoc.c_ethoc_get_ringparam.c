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
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; int /*<<< orphan*/  rx_pending; scalar_t__ tx_max_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; scalar_t__ rx_max_pending; } ;
struct ethoc {int /*<<< orphan*/  num_tx; int /*<<< orphan*/  num_rx; scalar_t__ num_bd; } ;

/* Variables and functions */
 struct ethoc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ethoc_get_ringparam(struct net_device *dev,
				struct ethtool_ringparam *ring)
{
	struct ethoc *priv = netdev_priv(dev);

	ring->rx_max_pending = priv->num_bd - 1;
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->tx_max_pending = priv->num_bd - 1;

	ring->rx_pending = priv->num_rx;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
	ring->tx_pending = priv->num_tx;
}