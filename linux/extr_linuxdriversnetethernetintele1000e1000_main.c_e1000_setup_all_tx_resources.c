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
struct e1000_adapter {int num_tx_queues; int /*<<< orphan*/ * tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_free_tx_resources (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 int e1000_setup_tx_resources (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  probe ; 

int e1000_setup_all_tx_resources(struct e1000_adapter *adapter)
{
	int i, err = 0;

	for (i = 0; i < adapter->num_tx_queues; i++) {
		err = e1000_setup_tx_resources(adapter, &adapter->tx_ring[i]);
		if (err) {
			e_err(probe, "Allocation for Tx Queue %u failed\n", i);
			for (i-- ; i >= 0; i--)
				e1000_free_tx_resources(adapter,
							&adapter->tx_ring[i]);
			break;
		}
	}

	return err;
}