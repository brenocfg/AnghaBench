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
struct e1000_adapter {int num_tx_queues; int num_rx_queues; int /*<<< orphan*/  flags; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  rx_buffer_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAXIMUM_ETHERNET_VLAN_SIZE ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 scalar_t__ e1000_alloc_queues (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_disable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int e1000_sw_init(struct e1000_adapter *adapter)
{
	adapter->rx_buffer_len = MAXIMUM_ETHERNET_VLAN_SIZE;

	adapter->num_tx_queues = 1;
	adapter->num_rx_queues = 1;

	if (e1000_alloc_queues(adapter)) {
		e_err(probe, "Unable to allocate memory for queues\n");
		return -ENOMEM;
	}

	/* Explicitly disable IRQ since the NIC can be in any state. */
	e1000_irq_disable(adapter);

	spin_lock_init(&adapter->stats_lock);

	set_bit(__E1000_DOWN, &adapter->flags);

	return 0;
}