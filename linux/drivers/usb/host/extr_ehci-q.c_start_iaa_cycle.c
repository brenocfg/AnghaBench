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
struct ehci_hcd {scalar_t__ rh_state; int iaa_in_progress; int command; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int CMD_IAAD ; 
 int /*<<< orphan*/  EHCI_HRTIMER_IAA_WATCHDOG ; 
 scalar_t__ EHCI_RH_RUNNING ; 
 int /*<<< orphan*/  ehci_enable_event (struct ehci_hcd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_unlink_async (struct ehci_hcd*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void start_iaa_cycle(struct ehci_hcd *ehci)
{
	/* If the controller isn't running, we don't have to wait for it */
	if (unlikely(ehci->rh_state < EHCI_RH_RUNNING)) {
		end_unlink_async(ehci);

	/* Otherwise start a new IAA cycle if one isn't already running */
	} else if (ehci->rh_state == EHCI_RH_RUNNING &&
			!ehci->iaa_in_progress) {

		/* Make sure the unlinks are all visible to the hardware */
		wmb();

		ehci_writel(ehci, ehci->command | CMD_IAAD,
				&ehci->regs->command);
		ehci_readl(ehci, &ehci->regs->command);
		ehci->iaa_in_progress = true;
		ehci_enable_event(ehci, EHCI_HRTIMER_IAA_WATCHDOG, true);
	}
}