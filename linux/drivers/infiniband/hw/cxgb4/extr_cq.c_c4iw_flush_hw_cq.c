#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct t4_cqe {int /*<<< orphan*/  header; } ;
struct t4_swsqe {int complete; struct t4_cqe cqe; } ;
struct TYPE_11__ {struct t4_swsqe* sw_sq; TYPE_1__* oldest_read; } ;
struct TYPE_13__ {int flushed; TYPE_2__ sq; } ;
struct c4iw_qp {int /*<<< orphan*/  lock; TYPE_6__ wq; } ;
struct TYPE_12__ {size_t sw_pidx; struct t4_cqe* sw_queue; int /*<<< orphan*/  cqid; } ;
struct c4iw_cq {TYPE_3__ cq; int /*<<< orphan*/  rhp; } ;
struct TYPE_10__ {int /*<<< orphan*/  signaled; } ;

/* Variables and functions */
 scalar_t__ CQE_OPCODE (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_QPID (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_SWCQE_V (int) ; 
 int CQE_TYPE (struct t4_cqe*) ; 
 size_t CQE_WRID_SQ_IDX (struct t4_cqe*) ; 
 int CQE_WRID_STAG (struct t4_cqe*) ; 
 scalar_t__ FW_RI_READ_RESP ; 
 scalar_t__ FW_RI_TERMINATE ; 
 scalar_t__ SQ_TYPE (struct t4_cqe*) ; 
 int /*<<< orphan*/  advance_oldest_read (TYPE_6__*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_read_req_cqe (TYPE_6__*,struct t4_cqe*,struct t4_cqe*) ; 
 int /*<<< orphan*/  flush_completed_wrs (TYPE_6__*,TYPE_3__*) ; 
 struct c4iw_qp* get_qhp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_hwcq_consume (TYPE_3__*) ; 
 int t4_next_hw_cqe (TYPE_3__*,struct t4_cqe**) ; 
 int /*<<< orphan*/  t4_swcq_produce (TYPE_3__*) ; 

void c4iw_flush_hw_cq(struct c4iw_cq *chp, struct c4iw_qp *flush_qhp)
{
	struct t4_cqe *hw_cqe, *swcqe, read_cqe;
	struct c4iw_qp *qhp;
	struct t4_swsqe *swsqe;
	int ret;

	pr_debug("cqid 0x%x\n", chp->cq.cqid);
	ret = t4_next_hw_cqe(&chp->cq, &hw_cqe);

	/*
	 * This logic is similar to poll_cq(), but not quite the same
	 * unfortunately.  Need to move pertinent HW CQEs to the SW CQ but
	 * also do any translation magic that poll_cq() normally does.
	 */
	while (!ret) {
		qhp = get_qhp(chp->rhp, CQE_QPID(hw_cqe));

		/*
		 * drop CQEs with no associated QP
		 */
		if (qhp == NULL)
			goto next_cqe;

		if (flush_qhp != qhp) {
			spin_lock(&qhp->lock);

			if (qhp->wq.flushed == 1)
				goto next_cqe;
		}

		if (CQE_OPCODE(hw_cqe) == FW_RI_TERMINATE)
			goto next_cqe;

		if (CQE_OPCODE(hw_cqe) == FW_RI_READ_RESP) {

			/* If we have reached here because of async
			 * event or other error, and have egress error
			 * then drop
			 */
			if (CQE_TYPE(hw_cqe) == 1)
				goto next_cqe;

			/* drop peer2peer RTR reads.
			 */
			if (CQE_WRID_STAG(hw_cqe) == 1)
				goto next_cqe;

			/*
			 * Eat completions for unsignaled read WRs.
			 */
			if (!qhp->wq.sq.oldest_read->signaled) {
				advance_oldest_read(&qhp->wq);
				goto next_cqe;
			}

			/*
			 * Don't write to the HWCQ, create a new read req CQE
			 * in local memory and move it into the swcq.
			 */
			create_read_req_cqe(&qhp->wq, hw_cqe, &read_cqe);
			hw_cqe = &read_cqe;
			advance_oldest_read(&qhp->wq);
		}

		/* if its a SQ completion, then do the magic to move all the
		 * unsignaled and now in-order completions into the swcq.
		 */
		if (SQ_TYPE(hw_cqe)) {
			swsqe = &qhp->wq.sq.sw_sq[CQE_WRID_SQ_IDX(hw_cqe)];
			swsqe->cqe = *hw_cqe;
			swsqe->complete = 1;
			flush_completed_wrs(&qhp->wq, &chp->cq);
		} else {
			swcqe = &chp->cq.sw_queue[chp->cq.sw_pidx];
			*swcqe = *hw_cqe;
			swcqe->header |= cpu_to_be32(CQE_SWCQE_V(1));
			t4_swcq_produce(&chp->cq);
		}
next_cqe:
		t4_hwcq_consume(&chp->cq);
		ret = t4_next_hw_cqe(&chp->cq, &hw_cqe);
		if (qhp && flush_qhp != qhp)
			spin_unlock(&qhp->lock);
	}
}