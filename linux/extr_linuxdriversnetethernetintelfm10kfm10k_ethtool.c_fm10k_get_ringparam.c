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
struct fm10k_intfc {int /*<<< orphan*/  tx_ring_count; int /*<<< orphan*/  rx_ring_count; } ;
struct ethtool_ringparam {scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_MAX_RXD ; 
 int /*<<< orphan*/  FM10K_MAX_TXD ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fm10k_get_ringparam(struct net_device *netdev,
				struct ethtool_ringparam *ring)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);

	ring->rx_max_pending = FM10K_MAX_RXD;
	ring->tx_max_pending = FM10K_MAX_TXD;
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->rx_pending = interface->rx_ring_count;
	ring->tx_pending = interface->tx_ring_count;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
}