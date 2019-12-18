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
struct igb_ring {int dummy; } ;
struct igb_adapter {int num_rx_queues; struct igb_ring** rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  igb_configure_rx_ring (struct igb_adapter*,struct igb_ring*) ; 
 int /*<<< orphan*/  igb_set_default_mac_filter (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_set_rx_buffer_len (struct igb_adapter*,struct igb_ring*) ; 

__attribute__((used)) static void igb_configure_rx(struct igb_adapter *adapter)
{
	int i;

	/* set the correct pool for the PF default MAC address in entry 0 */
	igb_set_default_mac_filter(adapter);

	/* Setup the HW Rx Head and Tail Descriptor Pointers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	for (i = 0; i < adapter->num_rx_queues; i++) {
		struct igb_ring *rx_ring = adapter->rx_ring[i];

		igb_set_rx_buffer_len(adapter, rx_ring);
		igb_configure_rx_ring(adapter, rx_ring);
	}
}