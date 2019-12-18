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
struct usb_hcd {int dummy; } ;
struct ehci_hcd {int amd_pll_fix; TYPE_1__* regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  hrtimer; scalar_t__ enabled_hrtimer_events; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_status (struct ehci_hcd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*) ; 
 int /*<<< orphan*/  ehci_mem_cleanup (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_quiesce (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_reset (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_silence_controller (struct ehci_hcd*) ; 
 int /*<<< orphan*/  end_free_itds (struct ehci_hcd*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_debug_files (struct ehci_hcd*) ; 
 int /*<<< orphan*/  remove_sysfs_files (struct ehci_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_amd_dev_put () ; 

__attribute__((used)) static void ehci_stop (struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);

	ehci_dbg (ehci, "stop\n");

	/* no more interrupts ... */

	spin_lock_irq(&ehci->lock);
	ehci->enabled_hrtimer_events = 0;
	spin_unlock_irq(&ehci->lock);

	ehci_quiesce(ehci);
	ehci_silence_controller(ehci);
	ehci_reset (ehci);

	hrtimer_cancel(&ehci->hrtimer);
	remove_sysfs_files(ehci);
	remove_debug_files (ehci);

	/* root hub is shut down separately (first, when possible) */
	spin_lock_irq (&ehci->lock);
	end_free_itds(ehci);
	spin_unlock_irq (&ehci->lock);
	ehci_mem_cleanup (ehci);

	if (ehci->amd_pll_fix == 1)
		usb_amd_dev_put();

	dbg_status (ehci, "ehci_stop completed",
		    ehci_readl(ehci, &ehci->regs->status));
}