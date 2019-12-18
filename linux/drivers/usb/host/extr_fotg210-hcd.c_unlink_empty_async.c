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
struct fotg210_qh {scalar_t__ qh_state; scalar_t__ unlink_cycle; int /*<<< orphan*/  qtd_list; TYPE_3__ qh_next; } ;
struct fotg210_hcd {scalar_t__ rh_state; scalar_t__ async_unlink_cycle; scalar_t__ async_unlink; TYPE_2__* async; } ;
struct TYPE_4__ {struct fotg210_qh* qh; } ;
struct TYPE_5__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOTG210_HRTIMER_ASYNC_UNLINKS ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 scalar_t__ QH_STATE_LINKED ; 
 int /*<<< orphan*/  fotg210_enable_event (struct fotg210_hcd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  single_unlink_async (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  start_iaa_cycle (struct fotg210_hcd*,int) ; 

__attribute__((used)) static void unlink_empty_async(struct fotg210_hcd *fotg210)
{
	struct fotg210_qh *qh, *next;
	bool stopped = (fotg210->rh_state < FOTG210_RH_RUNNING);
	bool check_unlinks_later = false;

	/* Unlink all the async QHs that have been empty for a timer cycle */
	next = fotg210->async->qh_next.qh;
	while (next) {
		qh = next;
		next = qh->qh_next.qh;

		if (list_empty(&qh->qtd_list) &&
				qh->qh_state == QH_STATE_LINKED) {
			if (!stopped && qh->unlink_cycle ==
					fotg210->async_unlink_cycle)
				check_unlinks_later = true;
			else
				single_unlink_async(fotg210, qh);
		}
	}

	/* Start a new IAA cycle if any QHs are waiting for it */
	if (fotg210->async_unlink)
		start_iaa_cycle(fotg210, false);

	/* QHs that haven't been empty for long enough will be handled later */
	if (check_unlinks_later) {
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_ASYNC_UNLINKS,
				true);
		++fotg210->async_unlink_cycle;
	}
}