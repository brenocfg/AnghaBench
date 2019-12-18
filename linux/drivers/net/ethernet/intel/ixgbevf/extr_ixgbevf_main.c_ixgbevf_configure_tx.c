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
typedef  size_t u32 ;
struct ixgbevf_adapter {size_t num_tx_queues; size_t num_xdp_queues; int /*<<< orphan*/ * xdp_ring; int /*<<< orphan*/ * tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbevf_configure_tx_ring (struct ixgbevf_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbevf_configure_tx(struct ixgbevf_adapter *adapter)
{
	u32 i;

	/* Setup the HW Tx Head and Tail descriptor pointers */
	for (i = 0; i < adapter->num_tx_queues; i++)
		ixgbevf_configure_tx_ring(adapter, adapter->tx_ring[i]);
	for (i = 0; i < adapter->num_xdp_queues; i++)
		ixgbevf_configure_tx_ring(adapter, adapter->xdp_ring[i]);
}