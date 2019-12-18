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
struct ixgbevf_adapter {int num_rx_queues; int /*<<< orphan*/  state; int /*<<< orphan*/  num_xdp_queues; int /*<<< orphan*/  num_tx_queues; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  hw_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int ixgbevf_alloc_q_vectors (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset_interrupt_capability (struct ixgbevf_adapter*) ; 
 int ixgbevf_set_interrupt_capability (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_set_num_queues (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbevf_init_interrupt_scheme(struct ixgbevf_adapter *adapter)
{
	int err;

	/* Number of supported queues */
	ixgbevf_set_num_queues(adapter);

	err = ixgbevf_set_interrupt_capability(adapter);
	if (err) {
		hw_dbg(&adapter->hw,
		       "Unable to setup interrupt capabilities\n");
		goto err_set_interrupt;
	}

	err = ixgbevf_alloc_q_vectors(adapter);
	if (err) {
		hw_dbg(&adapter->hw, "Unable to allocate memory for queue vectors\n");
		goto err_alloc_q_vectors;
	}

	hw_dbg(&adapter->hw, "Multiqueue %s: Rx Queue count = %u, Tx Queue count = %u XDP Queue count %u\n",
	       (adapter->num_rx_queues > 1) ? "Enabled" : "Disabled",
	       adapter->num_rx_queues, adapter->num_tx_queues,
	       adapter->num_xdp_queues);

	set_bit(__IXGBEVF_DOWN, &adapter->state);

	return 0;
err_alloc_q_vectors:
	ixgbevf_reset_interrupt_capability(adapter);
err_set_interrupt:
	return err;
}