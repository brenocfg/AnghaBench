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
struct ixgbe_adapter {int num_tx_queues; int num_xdp_queues; int /*<<< orphan*/ * xdp_ring; int /*<<< orphan*/ * tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_clean_tx_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_clean_all_tx_rings(struct ixgbe_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_tx_queues; i++)
		ixgbe_clean_tx_ring(adapter->tx_ring[i]);
	for (i = 0; i < adapter->num_xdp_queues; i++)
		ixgbe_clean_tx_ring(adapter->xdp_ring[i]);
}