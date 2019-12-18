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
struct TYPE_6__ {struct ehci_qh* qh; } ;
struct ehci_qh {scalar_t__ qh_state; scalar_t__ unlink_cycle; int /*<<< orphan*/  unlink_reason; int /*<<< orphan*/  qtd_list; TYPE_3__ qh_next; } ;
struct ehci_hcd {scalar_t__ async_unlink_cycle; int /*<<< orphan*/  async_unlink; TYPE_2__* async; } ;
struct TYPE_4__ {struct ehci_qh* qh; } ;
struct TYPE_5__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_HRTIMER_ASYNC_UNLINKS ; 
 scalar_t__ QH_STATE_LINKED ; 
 int /*<<< orphan*/  QH_UNLINK_QUEUE_EMPTY ; 
 int /*<<< orphan*/  ehci_enable_event (struct ehci_hcd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_unlink_async (struct ehci_hcd*,struct ehci_qh*) ; 

__attribute__((used)) static void unlink_empty_async(struct ehci_hcd *ehci)
{
	struct ehci_qh		*qh;
	struct ehci_qh		*qh_to_unlink = NULL;
	int			count = 0;

	/* Find the last async QH which has been empty for a timer cycle */
	for (qh = ehci->async->qh_next.qh; qh; qh = qh->qh_next.qh) {
		if (list_empty(&qh->qtd_list) &&
				qh->qh_state == QH_STATE_LINKED) {
			++count;
			if (qh->unlink_cycle != ehci->async_unlink_cycle)
				qh_to_unlink = qh;
		}
	}

	/* If nothing else is being unlinked, unlink the last empty QH */
	if (list_empty(&ehci->async_unlink) && qh_to_unlink) {
		qh_to_unlink->unlink_reason |= QH_UNLINK_QUEUE_EMPTY;
		start_unlink_async(ehci, qh_to_unlink);
		--count;
	}

	/* Other QHs will be handled later */
	if (count > 0) {
		ehci_enable_event(ehci, EHCI_HRTIMER_ASYNC_UNLINKS, true);
		++ehci->async_unlink_cycle;
	}
}