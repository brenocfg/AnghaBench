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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  lost_iaa; } ;
struct ehci_hcd {scalar_t__ rh_state; TYPE_2__* regs; TYPE_1__ stats; int /*<<< orphan*/  iaa_in_progress; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int CMD_IAAD ; 
 scalar_t__ EHCI_RH_RUNNING ; 
 int /*<<< orphan*/  INCR (int /*<<< orphan*/ ) ; 
 int STS_IAA ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,int,int) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_iaa_cycle (struct ehci_hcd*) ; 

__attribute__((used)) static void ehci_iaa_watchdog(struct ehci_hcd *ehci)
{
	u32 cmd, status;

	/*
	 * Lost IAA irqs wedge things badly; seen first with a vt8235.
	 * So we need this watchdog, but must protect it against both
	 * (a) SMP races against real IAA firing and retriggering, and
	 * (b) clean HC shutdown, when IAA watchdog was pending.
	 */
	if (!ehci->iaa_in_progress || ehci->rh_state != EHCI_RH_RUNNING)
		return;

	/* If we get here, IAA is *REALLY* late.  It's barely
	 * conceivable that the system is so busy that CMD_IAAD
	 * is still legitimately set, so let's be sure it's
	 * clear before we read STS_IAA.  (The HC should clear
	 * CMD_IAAD when it sets STS_IAA.)
	 */
	cmd = ehci_readl(ehci, &ehci->regs->command);

	/*
	 * If IAA is set here it either legitimately triggered
	 * after the watchdog timer expired (_way_ late, so we'll
	 * still count it as lost) ... or a silicon erratum:
	 * - VIA seems to set IAA without triggering the IRQ;
	 * - IAAD potentially cleared without setting IAA.
	 */
	status = ehci_readl(ehci, &ehci->regs->status);
	if ((status & STS_IAA) || !(cmd & CMD_IAAD)) {
		INCR(ehci->stats.lost_iaa);
		ehci_writel(ehci, STS_IAA, &ehci->regs->status);
	}

	ehci_dbg(ehci, "IAA watchdog: status %x cmd %x\n", status, cmd);
	end_iaa_cycle(ehci);
}