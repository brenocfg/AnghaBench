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
struct fotg210_qh {scalar_t__ qh_state; int needs_rescan; struct fotg210_qh* unlink_next; int /*<<< orphan*/  unlink_cycle; } ;
struct fotg210_hcd {scalar_t__ rh_state; int /*<<< orphan*/  intr_unlink_cycle; struct fotg210_qh* intr_unlink; scalar_t__ intr_unlinking; struct fotg210_qh* intr_unlink_last; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOTG210_HRTIMER_UNLINK_INTR ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 scalar_t__ QH_STATE_COMPLETING ; 
 scalar_t__ QH_STATE_LINKED ; 
 int /*<<< orphan*/  fotg210_enable_event (struct fotg210_hcd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fotg210_handle_intr_unlinks (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  qh_unlink_periodic (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void start_unlink_intr(struct fotg210_hcd *fotg210,
		struct fotg210_qh *qh)
{
	/* If the QH isn't linked then there's nothing we can do
	 * unless we were called during a giveback, in which case
	 * qh_completions() has to deal with it.
	 */
	if (qh->qh_state != QH_STATE_LINKED) {
		if (qh->qh_state == QH_STATE_COMPLETING)
			qh->needs_rescan = 1;
		return;
	}

	qh_unlink_periodic(fotg210, qh);

	/* Make sure the unlinks are visible before starting the timer */
	wmb();

	/*
	 * The EHCI spec doesn't say how long it takes the controller to
	 * stop accessing an unlinked interrupt QH.  The timer delay is
	 * 9 uframes; presumably that will be long enough.
	 */
	qh->unlink_cycle = fotg210->intr_unlink_cycle;

	/* New entries go at the end of the intr_unlink list */
	if (fotg210->intr_unlink)
		fotg210->intr_unlink_last->unlink_next = qh;
	else
		fotg210->intr_unlink = qh;
	fotg210->intr_unlink_last = qh;

	if (fotg210->intr_unlinking)
		;	/* Avoid recursive calls */
	else if (fotg210->rh_state < FOTG210_RH_RUNNING)
		fotg210_handle_intr_unlinks(fotg210);
	else if (fotg210->intr_unlink == qh) {
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_UNLINK_INTR,
				true);
		++fotg210->intr_unlink_cycle;
	}
}