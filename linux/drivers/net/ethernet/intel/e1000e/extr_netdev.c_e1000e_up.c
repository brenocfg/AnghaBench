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
struct e1000_adapter {scalar_t__ msix_entries; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_configure (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_configure_msix (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_trigger_lsc (struct e1000_adapter*) ; 

void e1000e_up(struct e1000_adapter *adapter)
{
	/* hardware has been reset, we need to reload some things */
	e1000_configure(adapter);

	clear_bit(__E1000_DOWN, &adapter->state);

	if (adapter->msix_entries)
		e1000_configure_msix(adapter);
	e1000_irq_enable(adapter);

	/* Tx queue started by watchdog timer when link is up */

	e1000e_trigger_lsc(adapter);
}