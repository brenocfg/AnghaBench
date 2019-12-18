#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int get_link_status; } ;
struct igc_hw {TYPE_1__ mac; } ;
struct igc_adapter {int num_q_vectors; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  netdev; TYPE_2__** q_vector; scalar_t__ msix_entries; int /*<<< orphan*/  state; struct igc_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_ICR ; 
 int /*<<< orphan*/  __IGC_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igc_assign_vector (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igc_configure (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_configure_msix (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_irq_enable (struct igc_adapter*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void igc_up(struct igc_adapter *adapter)
{
	struct igc_hw *hw = &adapter->hw;
	int i = 0;

	/* hardware has been reset, we need to reload some things */
	igc_configure(adapter);

	clear_bit(__IGC_DOWN, &adapter->state);

	for (i = 0; i < adapter->num_q_vectors; i++)
		napi_enable(&adapter->q_vector[i]->napi);

	if (adapter->msix_entries)
		igc_configure_msix(adapter);
	else
		igc_assign_vector(adapter->q_vector[0], 0);

	/* Clear any pending interrupts. */
	rd32(IGC_ICR);
	igc_irq_enable(adapter);

	netif_tx_start_all_queues(adapter->netdev);

	/* start the watchdog. */
	hw->mac.get_link_status = 1;
	schedule_work(&adapter->watchdog_task);
}