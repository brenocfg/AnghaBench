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
struct igbvf_ring {int /*<<< orphan*/  count; } ;
struct igbvf_adapter {struct igbvf_ring* rx_ring; struct igbvf_ring* tx_ring; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGBVF_MAX_RXD ; 
 int /*<<< orphan*/  IGBVF_MAX_TXD ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void igbvf_get_ringparam(struct net_device *netdev,
				struct ethtool_ringparam *ring)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	struct igbvf_ring *tx_ring = adapter->tx_ring;
	struct igbvf_ring *rx_ring = adapter->rx_ring;

	ring->rx_max_pending = IGBVF_MAX_RXD;
	ring->tx_max_pending = IGBVF_MAX_TXD;
	ring->rx_pending = rx_ring->count;
	ring->tx_pending = tx_ring->count;
}