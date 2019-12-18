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
struct ehci_hcd {TYPE_1__* regs; int /*<<< orphan*/  rh_state; int /*<<< orphan*/  died_poll_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  intr_enable; int /*<<< orphan*/  configured_flag; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_HRTIMER_POLL_DEAD ; 
 int /*<<< orphan*/  EHCI_RH_HALTED ; 
 int STS_HALT ; 
 int /*<<< orphan*/  ehci_enable_event (struct ehci_hcd*,int /*<<< orphan*/ ,int) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_warn (struct ehci_hcd*,char*) ; 
 int /*<<< orphan*/  ehci_work (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_unlink_async (struct ehci_hcd*) ; 

__attribute__((used)) static void ehci_handle_controller_death(struct ehci_hcd *ehci)
{
	if (!(ehci_readl(ehci, &ehci->regs->status) & STS_HALT)) {

		/* Give up after a few milliseconds */
		if (ehci->died_poll_count++ < 5) {
			/* Try again later */
			ehci_enable_event(ehci, EHCI_HRTIMER_POLL_DEAD, true);
			return;
		}
		ehci_warn(ehci, "Waited too long for the controller to stop, giving up\n");
	}

	/* Clean up the mess */
	ehci->rh_state = EHCI_RH_HALTED;
	ehci_writel(ehci, 0, &ehci->regs->configured_flag);
	ehci_writel(ehci, 0, &ehci->regs->intr_enable);
	ehci_work(ehci);
	end_unlink_async(ehci);

	/* Not in process context, so don't try to reset the controller */
}