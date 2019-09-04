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
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct ena_ring {int /*<<< orphan*/  ring_size; } ;
struct ena_adapter {struct ena_ring* rx_ring; struct ena_ring* tx_ring; } ;

/* Variables and functions */
 struct ena_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ena_get_ringparam(struct net_device *netdev,
			      struct ethtool_ringparam *ring)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	struct ena_ring *tx_ring = &adapter->tx_ring[0];
	struct ena_ring *rx_ring = &adapter->rx_ring[0];

	ring->rx_max_pending = rx_ring->ring_size;
	ring->tx_max_pending = tx_ring->ring_size;
	ring->rx_pending = rx_ring->ring_size;
	ring->tx_pending = tx_ring->ring_size;
}