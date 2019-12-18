#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct fotg210_qh* qh; } ;
struct fotg210_qh {scalar_t__ qh_state; int /*<<< orphan*/  unlink_cycle; int /*<<< orphan*/  qtd_list; scalar_t__ needs_rescan; TYPE_3__ qh_next; } ;
struct fotg210_hcd {scalar_t__ rh_state; int enabled_hrtimer_events; int /*<<< orphan*/  async_unlink_cycle; struct fotg210_qh* qh_scan_next; TYPE_2__* async; } ;
struct TYPE_4__ {struct fotg210_qh* qh; } ;
struct TYPE_5__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOTG210_HRTIMER_ASYNC_UNLINKS ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 scalar_t__ QH_STATE_LINKED ; 
 int /*<<< orphan*/  fotg210_enable_event (struct fotg210_hcd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int qh_completions (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  start_unlink_async (struct fotg210_hcd*,struct fotg210_qh*) ; 

__attribute__((used)) static void scan_async(struct fotg210_hcd *fotg210)
{
	struct fotg210_qh *qh;
	bool check_unlinks_later = false;

	fotg210->qh_scan_next = fotg210->async->qh_next.qh;
	while (fotg210->qh_scan_next) {
		qh = fotg210->qh_scan_next;
		fotg210->qh_scan_next = qh->qh_next.qh;
rescan:
		/* clean any finished work for this qh */
		if (!list_empty(&qh->qtd_list)) {
			int temp;

			/*
			 * Unlinks could happen here; completion reporting
			 * drops the lock.  That's why fotg210->qh_scan_next
			 * always holds the next qh to scan; if the next qh
			 * gets unlinked then fotg210->qh_scan_next is adjusted
			 * in single_unlink_async().
			 */
			temp = qh_completions(fotg210, qh);
			if (qh->needs_rescan) {
				start_unlink_async(fotg210, qh);
			} else if (list_empty(&qh->qtd_list)
					&& qh->qh_state == QH_STATE_LINKED) {
				qh->unlink_cycle = fotg210->async_unlink_cycle;
				check_unlinks_later = true;
			} else if (temp != 0)
				goto rescan;
		}
	}

	/*
	 * Unlink empty entries, reducing DMA usage as well
	 * as HCD schedule-scanning costs.  Delay for any qh
	 * we just scanned, there's a not-unusual case that it
	 * doesn't stay idle for long.
	 */
	if (check_unlinks_later && fotg210->rh_state == FOTG210_RH_RUNNING &&
			!(fotg210->enabled_hrtimer_events &
			BIT(FOTG210_HRTIMER_ASYNC_UNLINKS))) {
		fotg210_enable_event(fotg210,
				FOTG210_HRTIMER_ASYNC_UNLINKS, true);
		++fotg210->async_unlink_cycle;
	}
}