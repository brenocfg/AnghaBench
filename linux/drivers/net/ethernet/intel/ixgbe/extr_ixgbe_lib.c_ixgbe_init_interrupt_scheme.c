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
struct ixgbe_adapter {int num_rx_queues; int /*<<< orphan*/  state; int /*<<< orphan*/  num_xdp_queues; int /*<<< orphan*/  num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  e_dev_err (char*) ; 
 int /*<<< orphan*/  e_dev_info (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ixgbe_alloc_q_vectors (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_cache_ring_register (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_reset_interrupt_capability (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_set_interrupt_capability (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_set_num_queues (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ixgbe_init_interrupt_scheme(struct ixgbe_adapter *adapter)
{
	int err;

	/* Number of supported queues */
	ixgbe_set_num_queues(adapter);

	/* Set interrupt mode */
	ixgbe_set_interrupt_capability(adapter);

	err = ixgbe_alloc_q_vectors(adapter);
	if (err) {
		e_dev_err("Unable to allocate memory for queue vectors\n");
		goto err_alloc_q_vectors;
	}

	ixgbe_cache_ring_register(adapter);

	e_dev_info("Multiqueue %s: Rx Queue count = %u, Tx Queue count = %u XDP Queue count = %u\n",
		   (adapter->num_rx_queues > 1) ? "Enabled" : "Disabled",
		   adapter->num_rx_queues, adapter->num_tx_queues,
		   adapter->num_xdp_queues);

	set_bit(__IXGBE_DOWN, &adapter->state);

	return 0;

err_alloc_q_vectors:
	ixgbe_reset_interrupt_capability(adapter);
	return err;
}