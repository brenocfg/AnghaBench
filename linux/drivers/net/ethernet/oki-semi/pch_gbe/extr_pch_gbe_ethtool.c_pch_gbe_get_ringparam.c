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
struct pch_gbe_tx_ring {int /*<<< orphan*/  count; } ;
struct pch_gbe_rx_ring {int /*<<< orphan*/  count; } ;
struct pch_gbe_adapter {struct pch_gbe_rx_ring* rx_ring; struct pch_gbe_tx_ring* tx_ring; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_GBE_MAX_RXD ; 
 int /*<<< orphan*/  PCH_GBE_MAX_TXD ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void pch_gbe_get_ringparam(struct net_device *netdev,
					struct ethtool_ringparam *ring)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct pch_gbe_tx_ring *txdr = adapter->tx_ring;
	struct pch_gbe_rx_ring *rxdr = adapter->rx_ring;

	ring->rx_max_pending = PCH_GBE_MAX_RXD;
	ring->tx_max_pending = PCH_GBE_MAX_TXD;
	ring->rx_pending = rxdr->count;
	ring->tx_pending = txdr->count;
}