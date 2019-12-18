#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ohci_hcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  intrenable; } ;

/* Variables and functions */
 int OHCI_INTR_RHSC ; 
 int ohci_readl (struct ohci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_writel (struct ohci_hcd*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ohci_root_hub_state_changes(struct ohci_hcd *ohci, int changed,
		int any_connected, int rhsc_status)
{
	/* If RHSC is enabled, don't poll */
	if (ohci_readl(ohci, &ohci->regs->intrenable) & OHCI_INTR_RHSC)
		return 0;

	/* If status changes are pending, continue polling.
	 * Conversely, if no status changes are pending but the RHSC
	 * status bit was set, then RHSC may be broken so continue polling.
	 */
	if (changed || rhsc_status)
		return 1;

	/* It's safe to re-enable RHSC interrupts */
	ohci_writel(ohci, OHCI_INTR_RHSC, &ohci->regs->intrenable);
	return 0;
}