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
struct e1000_hw {TYPE_1__ mac; } ;
struct igbvf_adapter {int /*<<< orphan*/  watchdog_timer; scalar_t__ msix_entries; TYPE_2__* rx_ring; int /*<<< orphan*/  state; struct e1000_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  EICR ; 
 int /*<<< orphan*/  __IGBVF_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igbvf_configure (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_configure_msix (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_irq_enable (struct igbvf_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

int igbvf_up(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	/* hardware has been reset, we need to reload some things */
	igbvf_configure(adapter);

	clear_bit(__IGBVF_DOWN, &adapter->state);

	napi_enable(&adapter->rx_ring->napi);
	if (adapter->msix_entries)
		igbvf_configure_msix(adapter);

	/* Clear any pending interrupts. */
	er32(EICR);
	igbvf_irq_enable(adapter);

	/* start the watchdog */
	hw->mac.get_link_status = 1;
	mod_timer(&adapter->watchdog_timer, jiffies + 1);

	return 0;
}