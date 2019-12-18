#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ opcode; } ;
struct rvt_swqe {TYPE_1__ wr; int /*<<< orphan*/  lpsn; } ;
struct rvt_qp {int /*<<< orphan*/  rspwait; int /*<<< orphan*/  r_flags; scalar_t__ s_last_psn; int /*<<< orphan*/  s_acked; int /*<<< orphan*/  s_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  n_rdma_seq; } ;
struct hfi1_ibport {TYPE_2__ rvp; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  qp_wait_list; } ;

/* Variables and functions */
 scalar_t__ IB_WR_ATOMIC_CMP_AND_SWP ; 
 scalar_t__ IB_WR_ATOMIC_FETCH_AND_ADD ; 
 scalar_t__ IB_WR_RDMA_READ ; 
 scalar_t__ IB_WR_TID_RDMA_READ ; 
 scalar_t__ IB_WR_TID_RDMA_WRITE ; 
 int /*<<< orphan*/  RVT_R_RDMAR_SEQ ; 
 int /*<<< orphan*/  RVT_R_RSP_SEND ; 
 scalar_t__ cmp_psn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rvt_swqe* do_rc_completion (struct rvt_qp*,struct rvt_swqe*,struct hfi1_ibport*) ; 
 int /*<<< orphan*/  hfi1_restart_rc (struct rvt_qp*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_get_qp (struct rvt_qp*) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_stop_rc_timers (struct rvt_qp*) ; 

__attribute__((used)) static void rdma_seq_err(struct rvt_qp *qp, struct hfi1_ibport *ibp, u32 psn,
			 struct hfi1_ctxtdata *rcd)
{
	struct rvt_swqe *wqe;

	lockdep_assert_held(&qp->s_lock);
	/* Remove QP from retry timer */
	rvt_stop_rc_timers(qp);

	wqe = rvt_get_swqe_ptr(qp, qp->s_acked);

	while (cmp_psn(psn, wqe->lpsn) > 0) {
		if (wqe->wr.opcode == IB_WR_RDMA_READ ||
		    wqe->wr.opcode == IB_WR_TID_RDMA_READ ||
		    wqe->wr.opcode == IB_WR_TID_RDMA_WRITE ||
		    wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD)
			break;
		wqe = do_rc_completion(qp, wqe, ibp);
	}

	ibp->rvp.n_rdma_seq++;
	qp->r_flags |= RVT_R_RDMAR_SEQ;
	hfi1_restart_rc(qp, qp->s_last_psn + 1, 0);
	if (list_empty(&qp->rspwait)) {
		qp->r_flags |= RVT_R_RSP_SEND;
		rvt_get_qp(qp);
		list_add_tail(&qp->rspwait, &rcd->qp_wait_list);
	}
}