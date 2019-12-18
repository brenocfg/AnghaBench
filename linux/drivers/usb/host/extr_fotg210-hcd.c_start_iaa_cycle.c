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
struct fotg210_hcd {scalar_t__ rh_state; int command; TYPE_1__* regs; int /*<<< orphan*/ * async_unlink; int /*<<< orphan*/ * async_iaa; scalar_t__ async_unlinking; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int CMD_IAAD ; 
 int /*<<< orphan*/  FOTG210_HRTIMER_IAA_WATCHDOG ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 int /*<<< orphan*/  end_unlink_async (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_enable_event (struct fotg210_hcd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fotg210_writel (struct fotg210_hcd*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void start_iaa_cycle(struct fotg210_hcd *fotg210, bool nested)
{
	/*
	 * Do nothing if an IAA cycle is already running or
	 * if one will be started shortly.
	 */
	if (fotg210->async_iaa || fotg210->async_unlinking)
		return;

	/* Do all the waiting QHs at once */
	fotg210->async_iaa = fotg210->async_unlink;
	fotg210->async_unlink = NULL;

	/* If the controller isn't running, we don't have to wait for it */
	if (unlikely(fotg210->rh_state < FOTG210_RH_RUNNING)) {
		if (!nested)		/* Avoid recursion */
			end_unlink_async(fotg210);

	/* Otherwise start a new IAA cycle */
	} else if (likely(fotg210->rh_state == FOTG210_RH_RUNNING)) {
		/* Make sure the unlinks are all visible to the hardware */
		wmb();

		fotg210_writel(fotg210, fotg210->command | CMD_IAAD,
				&fotg210->regs->command);
		fotg210_readl(fotg210, &fotg210->regs->command);
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_IAA_WATCHDOG,
				true);
	}
}