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
struct ixgbe_adapter {int num_q_vectors; scalar_t__ num_rx_queues; scalar_t__ num_xdp_queues; scalar_t__ num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_free_q_vector (struct ixgbe_adapter*,int) ; 

__attribute__((used)) static void ixgbe_free_q_vectors(struct ixgbe_adapter *adapter)
{
	int v_idx = adapter->num_q_vectors;

	adapter->num_tx_queues = 0;
	adapter->num_xdp_queues = 0;
	adapter->num_rx_queues = 0;
	adapter->num_q_vectors = 0;

	while (v_idx--)
		ixgbe_free_q_vector(adapter, v_idx);
}