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
struct mvpp2_port {int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_MAX_RXD_MAX ; 
 int /*<<< orphan*/  MVPP2_MAX_TXD_MAX ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mvpp2_ethtool_get_ringparam(struct net_device *dev,
					struct ethtool_ringparam *ring)
{
	struct mvpp2_port *port = netdev_priv(dev);

	ring->rx_max_pending = MVPP2_MAX_RXD_MAX;
	ring->tx_max_pending = MVPP2_MAX_TXD_MAX;
	ring->rx_pending = port->rx_ring_size;
	ring->tx_pending = port->tx_ring_size;
}