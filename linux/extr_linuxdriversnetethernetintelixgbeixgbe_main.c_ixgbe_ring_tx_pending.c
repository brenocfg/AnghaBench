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
struct ixgbe_ring {scalar_t__ next_to_use; scalar_t__ next_to_clean; } ;
struct ixgbe_adapter {int num_tx_queues; int num_xdp_queues; struct ixgbe_ring** xdp_ring; struct ixgbe_ring** tx_ring; } ;

/* Variables and functions */

__attribute__((used)) static bool ixgbe_ring_tx_pending(struct ixgbe_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_tx_queues; i++) {
		struct ixgbe_ring *tx_ring = adapter->tx_ring[i];

		if (tx_ring->next_to_use != tx_ring->next_to_clean)
			return true;
	}

	for (i = 0; i < adapter->num_xdp_queues; i++) {
		struct ixgbe_ring *ring = adapter->xdp_ring[i];

		if (ring->next_to_use != ring->next_to_clean)
			return true;
	}

	return false;
}