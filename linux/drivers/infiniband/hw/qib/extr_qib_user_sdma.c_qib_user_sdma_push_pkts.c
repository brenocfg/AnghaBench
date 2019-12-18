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
struct qib_user_sdma_queue {int num_pending; TYPE_1__* sdma_rb_node; } ;
struct list_head {int dummy; } ;
struct qib_pportdata {int lflags; int /*<<< orphan*/  sdma_lock; struct list_head sdma_userpending; } ;
struct TYPE_2__ {int refcount; } ;

/* Variables and functions */
 int ECOMM ; 
 int QIBL_LINKACTIVE ; 
 int /*<<< orphan*/  __qib_sdma_running (struct qib_pportdata*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_splice_tail_init (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  qib_sdma_make_progress (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_user_sdma_send_desc (struct qib_pportdata*,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int qib_user_sdma_push_pkts(struct qib_pportdata *ppd,
				 struct qib_user_sdma_queue *pq,
				 struct list_head *pktlist, int count)
{
	unsigned long flags;

	if (unlikely(!(ppd->lflags & QIBL_LINKACTIVE)))
		return -ECOMM;

	/* non-blocking mode */
	if (pq->sdma_rb_node->refcount > 1) {
		spin_lock_irqsave(&ppd->sdma_lock, flags);
		if (unlikely(!__qib_sdma_running(ppd))) {
			spin_unlock_irqrestore(&ppd->sdma_lock, flags);
			return -ECOMM;
		}
		pq->num_pending += count;
		list_splice_tail_init(pktlist, &ppd->sdma_userpending);
		qib_user_sdma_send_desc(ppd, &ppd->sdma_userpending);
		spin_unlock_irqrestore(&ppd->sdma_lock, flags);
		return 0;
	}

	/* In this case, descriptors from this process are not
	 * linked to ppd pending queue, interrupt handler
	 * won't update this process, it is OK to directly
	 * modify without sdma lock.
	 */


	pq->num_pending += count;
	/*
	 * Blocking mode for single rail process, we must
	 * release/regain sdma_lock to give other process
	 * chance to make progress. This is important for
	 * performance.
	 */
	do {
		spin_lock_irqsave(&ppd->sdma_lock, flags);
		if (unlikely(!__qib_sdma_running(ppd))) {
			spin_unlock_irqrestore(&ppd->sdma_lock, flags);
			return -ECOMM;
		}
		qib_user_sdma_send_desc(ppd, pktlist);
		if (!list_empty(pktlist))
			qib_sdma_make_progress(ppd);
		spin_unlock_irqrestore(&ppd->sdma_lock, flags);
	} while (!list_empty(pktlist));

	return 0;
}