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
struct qib_user_sdma_queue {scalar_t__ added; int counter; int /*<<< orphan*/  lock; scalar_t__ num_sending; } ;
struct qib_pportdata {scalar_t__ sdma_descq_removed; } ;
struct qib_devdata {TYPE_1__* pcidev; } ;
struct qib_ctxtdata {struct qib_pportdata* ppd; struct qib_devdata* dd; } ;
struct list_head {int dummy; } ;
struct iovec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qib_sdma_descq_freecnt (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_sdma_running (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_user_sdma_free_pkt_list (int /*<<< orphan*/ *,struct qib_user_sdma_queue*,struct list_head*) ; 
 int /*<<< orphan*/  qib_user_sdma_hwqueue_clean (struct qib_pportdata*) ; 
 int qib_user_sdma_push_pkts (struct qib_pportdata*,struct qib_user_sdma_queue*,struct list_head*,int) ; 
 int /*<<< orphan*/  qib_user_sdma_queue_clean (struct qib_pportdata*,struct qib_user_sdma_queue*) ; 
 int qib_user_sdma_queue_pkts (struct qib_devdata*,struct qib_pportdata*,struct qib_user_sdma_queue*,struct iovec const*,unsigned long,struct list_head*,int*,int*) ; 

int qib_user_sdma_writev(struct qib_ctxtdata *rcd,
			 struct qib_user_sdma_queue *pq,
			 const struct iovec *iov,
			 unsigned long dim)
{
	struct qib_devdata *dd = rcd->dd;
	struct qib_pportdata *ppd = rcd->ppd;
	int ret = 0;
	struct list_head list;
	int npkts = 0;

	INIT_LIST_HEAD(&list);

	mutex_lock(&pq->lock);

	/* why not -ECOMM like qib_user_sdma_push_pkts() below? */
	if (!qib_sdma_running(ppd))
		goto done_unlock;

	/* if I have packets not complete yet */
	if (pq->added > ppd->sdma_descq_removed)
		qib_user_sdma_hwqueue_clean(ppd);
	/* if I have complete packets to be freed */
	if (pq->num_sending)
		qib_user_sdma_queue_clean(ppd, pq);

	while (dim) {
		int mxp = 1;
		int ndesc = 0;

		ret = qib_user_sdma_queue_pkts(dd, ppd, pq,
				iov, dim, &list, &mxp, &ndesc);
		if (ret < 0)
			goto done_unlock;
		else {
			dim -= ret;
			iov += ret;
		}

		/* force packets onto the sdma hw queue... */
		if (!list_empty(&list)) {
			/*
			 * Lazily clean hw queue.
			 */
			if (qib_sdma_descq_freecnt(ppd) < ndesc) {
				qib_user_sdma_hwqueue_clean(ppd);
				if (pq->num_sending)
					qib_user_sdma_queue_clean(ppd, pq);
			}

			ret = qib_user_sdma_push_pkts(ppd, pq, &list, mxp);
			if (ret < 0)
				goto done_unlock;
			else {
				npkts += mxp;
				pq->counter += mxp;
			}
		}
	}

done_unlock:
	if (!list_empty(&list))
		qib_user_sdma_free_pkt_list(&dd->pcidev->dev, pq, &list);
	mutex_unlock(&pq->lock);

	return (ret < 0) ? ret : npkts;
}