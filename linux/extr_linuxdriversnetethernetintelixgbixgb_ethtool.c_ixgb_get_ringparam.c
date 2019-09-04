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
struct ixgb_desc_ring {int /*<<< orphan*/  count; } ;
struct ixgb_adapter {struct ixgb_desc_ring rx_ring; struct ixgb_desc_ring tx_ring; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RXD ; 
 int /*<<< orphan*/  MAX_TXD ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
ixgb_get_ringparam(struct net_device *netdev,
		struct ethtool_ringparam *ring)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	struct ixgb_desc_ring *txdr = &adapter->tx_ring;
	struct ixgb_desc_ring *rxdr = &adapter->rx_ring;

	ring->rx_max_pending = MAX_RXD;
	ring->tx_max_pending = MAX_TXD;
	ring->rx_pending = rxdr->count;
	ring->tx_pending = txdr->count;
}