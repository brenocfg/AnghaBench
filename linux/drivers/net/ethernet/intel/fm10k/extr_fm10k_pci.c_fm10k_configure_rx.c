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
struct fm10k_intfc {int num_rx_queues; int /*<<< orphan*/ * rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_configure_dglort (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_configure_rx_ring (struct fm10k_intfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_configure_swpri_map (struct fm10k_intfc*) ; 

__attribute__((used)) static void fm10k_configure_rx(struct fm10k_intfc *interface)
{
	int i;

	/* Configure SWPRI to PC map */
	fm10k_configure_swpri_map(interface);

	/* Configure RSS and DGLORT map */
	fm10k_configure_dglort(interface);

	/* Setup the HW Rx Head and Tail descriptor pointers */
	for (i = 0; i < interface->num_rx_queues; i++)
		fm10k_configure_rx_ring(interface, interface->rx_ring[i]);

	/* possible poll here to verify that Rx rings are now enabled */
}