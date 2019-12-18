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
struct fotg210_hcd {TYPE_1__* regs; int /*<<< orphan*/  rh_state; int /*<<< orphan*/  died_poll_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  intr_enable; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOTG210_HRTIMER_POLL_DEAD ; 
 int /*<<< orphan*/  FOTG210_RH_HALTED ; 
 int STS_HALT ; 
 int /*<<< orphan*/  end_unlink_async (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_enable_event (struct fotg210_hcd*,int /*<<< orphan*/ ,int) ; 
 int fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fotg210_warn (struct fotg210_hcd*,char*) ; 
 int /*<<< orphan*/  fotg210_work (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_writel (struct fotg210_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fotg210_handle_controller_death(struct fotg210_hcd *fotg210)
{
	if (!(fotg210_readl(fotg210, &fotg210->regs->status) & STS_HALT)) {

		/* Give up after a few milliseconds */
		if (fotg210->died_poll_count++ < 5) {
			/* Try again later */
			fotg210_enable_event(fotg210,
					FOTG210_HRTIMER_POLL_DEAD, true);
			return;
		}
		fotg210_warn(fotg210, "Waited too long for the controller to stop, giving up\n");
	}

	/* Clean up the mess */
	fotg210->rh_state = FOTG210_RH_HALTED;
	fotg210_writel(fotg210, 0, &fotg210->regs->intr_enable);
	fotg210_work(fotg210);
	end_unlink_async(fotg210);

	/* Not in process context, so don't try to reset the controller */
}