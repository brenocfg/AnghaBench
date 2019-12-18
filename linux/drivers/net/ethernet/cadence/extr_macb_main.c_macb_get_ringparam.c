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
struct macb {int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RX_RING_SIZE ; 
 int /*<<< orphan*/  MAX_TX_RING_SIZE ; 
 struct macb* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void macb_get_ringparam(struct net_device *netdev,
			       struct ethtool_ringparam *ring)
{
	struct macb *bp = netdev_priv(netdev);

	ring->rx_max_pending = MAX_RX_RING_SIZE;
	ring->tx_max_pending = MAX_TX_RING_SIZE;

	ring->rx_pending = bp->rx_ring_size;
	ring->tx_pending = bp->tx_ring_size;
}