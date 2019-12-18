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
typedef  uintptr_t uint32_t ;
typedef  int uint16_t ;
struct csio_wrm {int free_qidx; struct csio_q** q_arr; } ;
struct csio_wr_pair {uintptr_t size1; uintptr_t size2; int /*<<< orphan*/ * addr2; void* addr1; } ;
struct csio_qstatus_page {int /*<<< orphan*/  cidx; } ;
struct csio_q {uintptr_t pidx; int cidx; int credits; int inc_idx; int /*<<< orphan*/ * vstart; scalar_t__ vwrap; int /*<<< orphan*/ * owner; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 uintptr_t ALIGN (uintptr_t,uintptr_t) ; 
 int /*<<< orphan*/  CSIO_DB_ASSERT (int) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_q*,int /*<<< orphan*/ ) ; 
 uintptr_t CSIO_QCREDIT_SZ ; 
 int EBUSY ; 
 struct csio_wrm* csio_hw_to_wrm (struct csio_hw*) ; 
 int /*<<< orphan*/  n_eq_wr_split ; 
 int /*<<< orphan*/  n_qempty ; 
 int /*<<< orphan*/  n_qfull ; 
 int /*<<< orphan*/  n_qwrap ; 
 int /*<<< orphan*/  n_tot_reqs ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int
csio_wr_get(struct csio_hw *hw, int qidx, uint32_t size,
	    struct csio_wr_pair *wrp)
{
	struct csio_wrm *wrm = csio_hw_to_wrm(hw);
	struct csio_q *q = wrm->q_arr[qidx];
	void *cwr = (void *)((uintptr_t)(q->vstart) +
						(q->pidx * CSIO_QCREDIT_SZ));
	struct csio_qstatus_page *stp = (struct csio_qstatus_page *)q->vwrap;
	uint16_t cidx = q->cidx = ntohs(stp->cidx);
	uint16_t pidx = q->pidx;
	uint32_t req_sz	= ALIGN(size, CSIO_QCREDIT_SZ);
	int req_credits	= req_sz / CSIO_QCREDIT_SZ;
	int credits;

	CSIO_DB_ASSERT(q->owner != NULL);
	CSIO_DB_ASSERT((qidx >= 0) && (qidx < wrm->free_qidx));
	CSIO_DB_ASSERT(cidx <= q->credits);

	/* Calculate credits */
	if (pidx > cidx) {
		credits = q->credits - (pidx - cidx) - 1;
	} else if (cidx > pidx) {
		credits = cidx - pidx - 1;
	} else {
		/* cidx == pidx, empty queue */
		credits = q->credits;
		CSIO_INC_STATS(q, n_qempty);
	}

	/*
	 * Check if we have enough credits.
	 * credits = 1 implies queue is full.
	 */
	if (!credits || (req_credits > credits)) {
		CSIO_INC_STATS(q, n_qfull);
		return -EBUSY;
	}

	/*
	 * If we are here, we have enough credits to satisfy the
	 * request. Check if we are near the end of q, and if WR spills over.
	 * If it does, use the first addr/size to cover the queue until
	 * the end. Fit the remainder portion of the request at the top
	 * of queue and return it in the second addr/len. Set pidx
	 * accordingly.
	 */
	if (unlikely(((uintptr_t)cwr + req_sz) > (uintptr_t)(q->vwrap))) {
		wrp->addr1 = cwr;
		wrp->size1 = (uint32_t)((uintptr_t)q->vwrap - (uintptr_t)cwr);
		wrp->addr2 = q->vstart;
		wrp->size2 = req_sz - wrp->size1;
		q->pidx	= (uint16_t)(ALIGN(wrp->size2, CSIO_QCREDIT_SZ) /
							CSIO_QCREDIT_SZ);
		CSIO_INC_STATS(q, n_qwrap);
		CSIO_INC_STATS(q, n_eq_wr_split);
	} else {
		wrp->addr1 = cwr;
		wrp->size1 = req_sz;
		wrp->addr2 = NULL;
		wrp->size2 = 0;
		q->pidx	+= (uint16_t)req_credits;

		/* We are the end of queue, roll back pidx to top of queue */
		if (unlikely(q->pidx == q->credits)) {
			q->pidx = 0;
			CSIO_INC_STATS(q, n_qwrap);
		}
	}

	q->inc_idx = (uint16_t)req_credits;

	CSIO_INC_STATS(q, n_tot_reqs);

	return 0;
}