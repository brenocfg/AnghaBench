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
struct igc_adapter {int num_q_vectors; scalar_t__ num_rx_queues; scalar_t__ num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  igc_free_q_vector (struct igc_adapter*,int) ; 
 int /*<<< orphan*/  igc_reset_q_vector (struct igc_adapter*,int) ; 

__attribute__((used)) static void igc_free_q_vectors(struct igc_adapter *adapter)
{
	int v_idx = adapter->num_q_vectors;

	adapter->num_tx_queues = 0;
	adapter->num_rx_queues = 0;
	adapter->num_q_vectors = 0;

	while (v_idx--) {
		igc_reset_q_vector(adapter, v_idx);
		igc_free_q_vector(adapter, v_idx);
	}
}