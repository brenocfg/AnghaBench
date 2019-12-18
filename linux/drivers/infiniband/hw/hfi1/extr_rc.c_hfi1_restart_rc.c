#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tid_rdma_request {int dummy; } ;
struct TYPE_7__ {scalar_t__ opcode; } ;
struct rvt_swqe {TYPE_3__ wr; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {scalar_t__ s_acked; scalar_t__ s_retry; scalar_t__ s_mig_state; scalar_t__ s_retry_cnt; scalar_t__ s_last; int s_flags; int /*<<< orphan*/  s_psn; int /*<<< orphan*/  port_num; TYPE_2__ ibqp; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  r_lock; struct hfi1_qp_priv* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  curr; } ;
struct hfi1_qp_priv {int /*<<< orphan*/  rcd; TYPE_1__ opfn; } ;
struct TYPE_8__ {scalar_t__ n_rc_resends; } ;
struct hfi1_ibport {TYPE_4__ rvp; } ;

/* Variables and functions */
 int HFI1_S_WAIT_TID_RESP ; 
 scalar_t__ IB_MIG_ARMED ; 
 int /*<<< orphan*/  IB_WC_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 scalar_t__ IB_WR_OPFN ; 
 scalar_t__ IB_WR_RDMA_READ ; 
 scalar_t__ IB_WR_TID_RDMA_READ ; 
 int RVT_S_SEND_ONE ; 
 int RVT_S_WAIT_ACK ; 
 int RVT_S_WAIT_FENCE ; 
 int RVT_S_WAIT_PSN ; 
 int RVT_S_WAIT_RDMAR ; 
 int RVT_S_WAIT_SSN_CREDIT ; 
 scalar_t__ delta_psn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rvt_swqe* do_rc_completion (struct rvt_qp*,struct rvt_swqe*,struct hfi1_ibport*) ; 
 int /*<<< orphan*/  hfi1_kern_clear_hw_flow (int /*<<< orphan*/ ,struct rvt_qp*) ; 
 int /*<<< orphan*/  hfi1_kern_exp_rcv_clear_all (struct tid_rdma_request*) ; 
 int /*<<< orphan*/  hfi1_migrate_qp (struct rvt_qp*) ; 
 int /*<<< orphan*/  hfi1_trdma_send_complete (struct rvt_qp*,struct rvt_swqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opfn_conn_reply (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_psn (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_error_qp (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 struct hfi1_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_sender_restart_rc (struct rvt_qp*) ; 
 int /*<<< orphan*/  trace_hfi1_tid_write_sender_restart_rc (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 struct tid_rdma_request* wqe_to_tid_req (struct rvt_swqe*) ; 

void hfi1_restart_rc(struct rvt_qp *qp, u32 psn, int wait)
{
	struct hfi1_qp_priv *priv = qp->priv;
	struct rvt_swqe *wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
	struct hfi1_ibport *ibp;

	lockdep_assert_held(&qp->r_lock);
	lockdep_assert_held(&qp->s_lock);
	trace_hfi1_sender_restart_rc(qp);
	if (qp->s_retry == 0) {
		if (qp->s_mig_state == IB_MIG_ARMED) {
			hfi1_migrate_qp(qp);
			qp->s_retry = qp->s_retry_cnt;
		} else if (qp->s_last == qp->s_acked) {
			/*
			 * We need special handling for the OPFN request WQEs as
			 * they are not allowed to generate real user errors
			 */
			if (wqe->wr.opcode == IB_WR_OPFN) {
				struct hfi1_ibport *ibp =
					to_iport(qp->ibqp.device, qp->port_num);
				/*
				 * Call opfn_conn_reply() with capcode and
				 * remaining data as 0 to close out the
				 * current request
				 */
				opfn_conn_reply(qp, priv->opfn.curr);
				wqe = do_rc_completion(qp, wqe, ibp);
				qp->s_flags &= ~RVT_S_WAIT_ACK;
			} else {
				trace_hfi1_tid_write_sender_restart_rc(qp, 0);
				if (wqe->wr.opcode == IB_WR_TID_RDMA_READ) {
					struct tid_rdma_request *req;

					req = wqe_to_tid_req(wqe);
					hfi1_kern_exp_rcv_clear_all(req);
					hfi1_kern_clear_hw_flow(priv->rcd, qp);
				}

				hfi1_trdma_send_complete(qp, wqe,
							 IB_WC_RETRY_EXC_ERR);
				rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
			}
			return;
		} else { /* need to handle delayed completion */
			return;
		}
	} else {
		qp->s_retry--;
	}

	ibp = to_iport(qp->ibqp.device, qp->port_num);
	if (wqe->wr.opcode == IB_WR_RDMA_READ ||
	    wqe->wr.opcode == IB_WR_TID_RDMA_READ)
		ibp->rvp.n_rc_resends++;
	else
		ibp->rvp.n_rc_resends += delta_psn(qp->s_psn, psn);

	qp->s_flags &= ~(RVT_S_WAIT_FENCE | RVT_S_WAIT_RDMAR |
			 RVT_S_WAIT_SSN_CREDIT | RVT_S_WAIT_PSN |
			 RVT_S_WAIT_ACK | HFI1_S_WAIT_TID_RESP);
	if (wait)
		qp->s_flags |= RVT_S_SEND_ONE;
	reset_psn(qp, psn);
}