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
struct ixgbevf_adapter {scalar_t__ num_rx_queues; scalar_t__ num_xdp_queues; scalar_t__ num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbevf_free_q_vectors (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset_interrupt_capability (struct ixgbevf_adapter*) ; 

__attribute__((used)) static void ixgbevf_clear_interrupt_scheme(struct ixgbevf_adapter *adapter)
{
	adapter->num_tx_queues = 0;
	adapter->num_xdp_queues = 0;
	adapter->num_rx_queues = 0;

	ixgbevf_free_q_vectors(adapter);
	ixgbevf_reset_interrupt_capability(adapter);
}