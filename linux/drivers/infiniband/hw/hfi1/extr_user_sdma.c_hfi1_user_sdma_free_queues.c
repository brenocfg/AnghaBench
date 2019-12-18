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
struct hfi1_user_sdma_pkt_q {int /*<<< orphan*/  comps; int /*<<< orphan*/  txreq_cache; struct hfi1_user_sdma_pkt_q* req_in_use; struct hfi1_user_sdma_pkt_q* reqs; int /*<<< orphan*/  n_reqs; int /*<<< orphan*/  wait; int /*<<< orphan*/  busy; scalar_t__ handler; } ;
struct hfi1_filedata {struct hfi1_user_sdma_pkt_q* cq; struct hfi1_user_sdma_pkt_q* pq; int /*<<< orphan*/  subctxt; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  ctxt; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_mmu_rb_unregister (scalar_t__) ; 
 int /*<<< orphan*/  iowait_sdma_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hfi1_user_sdma_pkt_q*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_user_free_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int hfi1_user_sdma_free_queues(struct hfi1_filedata *fd,
			       struct hfi1_ctxtdata *uctxt)
{
	struct hfi1_user_sdma_pkt_q *pq;

	trace_hfi1_sdma_user_free_queues(uctxt->dd, uctxt->ctxt, fd->subctxt);

	pq = fd->pq;
	if (pq) {
		if (pq->handler)
			hfi1_mmu_rb_unregister(pq->handler);
		iowait_sdma_drain(&pq->busy);
		/* Wait until all requests have been freed. */
		wait_event_interruptible(
			pq->wait,
			!atomic_read(&pq->n_reqs));
		kfree(pq->reqs);
		kfree(pq->req_in_use);
		kmem_cache_destroy(pq->txreq_cache);
		kfree(pq);
		fd->pq = NULL;
	}
	if (fd->cq) {
		vfree(fd->cq->comps);
		kfree(fd->cq);
		fd->cq = NULL;
	}
	return 0;
}