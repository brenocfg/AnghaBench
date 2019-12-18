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
struct fotg210_hcd {scalar_t__ rh_state; TYPE_2__* regs; TYPE_1__ stats; scalar_t__ async_iaa; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int CMD_IAAD ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 int /*<<< orphan*/  INCR (int /*<<< orphan*/ ) ; 
 int STS_IAA ; 
 int /*<<< orphan*/  end_unlink_async (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_dbg (struct fotg210_hcd*,char*,int,int) ; 
 int fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fotg210_writel (struct fotg210_hcd*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fotg210_iaa_watchdog(struct fotg210_hcd *fotg210)
{
	if (fotg210->rh_state != FOTG210_RH_RUNNING)
		return;

	/*
	 * Lost IAA irqs wedge things badly; seen first with a vt8235.
	 * So we need this watchdog, but must protect it against both
	 * (a) SMP races against real IAA firing and retriggering, and
	 * (b) clean HC shutdown, when IAA watchdog was pending.
	 */
	if (fotg210->async_iaa) {
		u32 cmd, status;

		/* If we get here, IAA is *REALLY* late.  It's barely
		 * conceivable that the system is so busy that CMD_IAAD
		 * is still legitimately set, so let's be sure it's
		 * clear before we read STS_IAA.  (The HC should clear
		 * CMD_IAAD when it sets STS_IAA.)
		 */
		cmd = fotg210_readl(fotg210, &fotg210->regs->command);

		/*
		 * If IAA is set here it either legitimately triggered
		 * after the watchdog timer expired (_way_ late, so we'll
		 * still count it as lost) ... or a silicon erratum:
		 * - VIA seems to set IAA without triggering the IRQ;
		 * - IAAD potentially cleared without setting IAA.
		 */
		status = fotg210_readl(fotg210, &fotg210->regs->status);
		if ((status & STS_IAA) || !(cmd & CMD_IAAD)) {
			INCR(fotg210->stats.lost_iaa);
			fotg210_writel(fotg210, STS_IAA,
					&fotg210->regs->status);
		}

		fotg210_dbg(fotg210, "IAA watchdog: status %x cmd %x\n",
				status, cmd);
		end_unlink_async(fotg210);
	}
}