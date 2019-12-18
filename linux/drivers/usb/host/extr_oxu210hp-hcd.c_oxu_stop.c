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
struct usb_hcd {int /*<<< orphan*/  state; } ;
struct oxu_hcd {TYPE_1__* regs; int /*<<< orphan*/  lock; scalar_t__ async; int /*<<< orphan*/  watchdog; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  configured_flag; int /*<<< orphan*/  intr_enable; } ;

/* Variables and functions */
 scalar_t__ HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_status (struct oxu_hcd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_mem_cleanup (struct oxu_hcd*) ; 
 int /*<<< orphan*/  ehci_port_power (struct oxu_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_quiesce (struct oxu_hcd*) ; 
 int /*<<< orphan*/  ehci_reset (struct oxu_hcd*) ; 
 int /*<<< orphan*/  ehci_work (struct oxu_hcd*) ; 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void oxu_stop(struct usb_hcd *hcd)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);

	/* Turn off port power on all root hub ports. */
	ehci_port_power(oxu, 0);

	/* no more interrupts ... */
	del_timer_sync(&oxu->watchdog);

	spin_lock_irq(&oxu->lock);
	if (HC_IS_RUNNING(hcd->state))
		ehci_quiesce(oxu);

	ehci_reset(oxu);
	writel(0, &oxu->regs->intr_enable);
	spin_unlock_irq(&oxu->lock);

	/* let companion controllers work when we aren't */
	writel(0, &oxu->regs->configured_flag);

	/* root hub is shut down separately (first, when possible) */
	spin_lock_irq(&oxu->lock);
	if (oxu->async)
		ehci_work(oxu);
	spin_unlock_irq(&oxu->lock);
	ehci_mem_cleanup(oxu);

	dbg_status(oxu, "oxu_stop completed", readl(&oxu->regs->status));
}