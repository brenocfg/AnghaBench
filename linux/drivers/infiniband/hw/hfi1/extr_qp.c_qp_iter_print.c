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
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct send_context {int /*<<< orphan*/  sw_index; } ;
struct sdma_engine {int /*<<< orphan*/  this_idx; } ;
struct TYPE_8__ {int /*<<< orphan*/  opcode; } ;
struct rvt_swqe {int /*<<< orphan*/  ssn; TYPE_1__ wr; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; } ;
struct rvt_srq {TYPE_3__ rq; } ;
struct rvt_qp_iter {int /*<<< orphan*/  n; struct rvt_qp* qp; } ;
struct TYPE_11__ {int /*<<< orphan*/  size; } ;
struct TYPE_9__ {size_t qp_type; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  device; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  srq; } ;
struct rvt_qp {size_t s_tail_ack_queue; TYPE_4__ r_rq; int /*<<< orphan*/  r_min_rnr_timer; int /*<<< orphan*/  s_ack_state; int /*<<< orphan*/  s_state; int /*<<< orphan*/  pid; TYPE_2__ ibqp; int /*<<< orphan*/  s_rnr_retry; int /*<<< orphan*/  s_rnr_retry_cnt; int /*<<< orphan*/  s_retry_cnt; int /*<<< orphan*/  s_retry; int /*<<< orphan*/  pmtu; int /*<<< orphan*/  remote_ah_attr; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  r_head_ack_queue; int /*<<< orphan*/  s_avail; int /*<<< orphan*/  s_size; int /*<<< orphan*/  s_head; int /*<<< orphan*/  s_tail; int /*<<< orphan*/  s_cur; int /*<<< orphan*/  s_acked; int /*<<< orphan*/  s_last; int /*<<< orphan*/  r_psn; int /*<<< orphan*/  s_sending_hpsn; int /*<<< orphan*/  s_sending_psn; int /*<<< orphan*/  s_next_psn; int /*<<< orphan*/  s_psn; int /*<<< orphan*/  s_last_psn; int /*<<< orphan*/  s_lsn; int /*<<< orphan*/  timeout; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  state; int /*<<< orphan*/  refcount; struct rvt_ack_entry* s_ack_queue; struct hfi1_qp_priv* priv; } ;
struct rvt_ack_entry {int /*<<< orphan*/  lpsn; int /*<<< orphan*/  psn; int /*<<< orphan*/  opcode; } ;
struct TYPE_13__ {int /*<<< orphan*/  list; } ;
struct hfi1_qp_priv {TYPE_6__ s_iowait; int /*<<< orphan*/  s_sc; } ;
struct TYPE_12__ {int /*<<< orphan*/  rdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_cq_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_cq_tail (int /*<<< orphan*/ ) ; 
 struct rvt_srq* ibsrq_to_rvtsrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowait_pio_pending (TYPE_6__*) ; 
 int /*<<< orphan*/  iowait_sdma_pending (TYPE_6__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ qp_idle (struct rvt_qp*) ; 
 struct sdma_engine* qp_to_sdma_engine (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 struct send_context* qp_to_send_context (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * qp_type_str ; 
 int /*<<< orphan*/  rdma_ah_get_dlid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_ah_get_sl (int /*<<< orphan*/ *) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_max_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdma_engine*,int /*<<< orphan*/ ,struct send_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* to_idev (int /*<<< orphan*/ ) ; 

void qp_iter_print(struct seq_file *s, struct rvt_qp_iter *iter)
{
	struct rvt_swqe *wqe;
	struct rvt_qp *qp = iter->qp;
	struct hfi1_qp_priv *priv = qp->priv;
	struct sdma_engine *sde;
	struct send_context *send_context;
	struct rvt_ack_entry *e = NULL;
	struct rvt_srq *srq = qp->ibqp.srq ?
		ibsrq_to_rvtsrq(qp->ibqp.srq) : NULL;

	sde = qp_to_sdma_engine(qp, priv->s_sc);
	wqe = rvt_get_swqe_ptr(qp, qp->s_last);
	send_context = qp_to_send_context(qp, priv->s_sc);
	if (qp->s_ack_queue)
		e = &qp->s_ack_queue[qp->s_tail_ack_queue];
	seq_printf(s,
		   "N %d %s QP %x R %u %s %u %u f=%x %u %u %u %u %u %u SPSN %x %x %x %x %x RPSN %x S(%u %u %u %u %u %u %u) R(%u %u %u) RQP %x LID %x SL %u MTU %u %u %u %u %u SDE %p,%u SC %p,%u SCQ %u %u PID %d OS %x %x E %x %x %x RNR %d %s %d\n",
		   iter->n,
		   qp_idle(qp) ? "I" : "B",
		   qp->ibqp.qp_num,
		   atomic_read(&qp->refcount),
		   qp_type_str[qp->ibqp.qp_type],
		   qp->state,
		   wqe ? wqe->wr.opcode : 0,
		   qp->s_flags,
		   iowait_sdma_pending(&priv->s_iowait),
		   iowait_pio_pending(&priv->s_iowait),
		   !list_empty(&priv->s_iowait.list),
		   qp->timeout,
		   wqe ? wqe->ssn : 0,
		   qp->s_lsn,
		   qp->s_last_psn,
		   qp->s_psn, qp->s_next_psn,
		   qp->s_sending_psn, qp->s_sending_hpsn,
		   qp->r_psn,
		   qp->s_last, qp->s_acked, qp->s_cur,
		   qp->s_tail, qp->s_head, qp->s_size,
		   qp->s_avail,
		   /* ack_queue ring pointers, size */
		   qp->s_tail_ack_queue, qp->r_head_ack_queue,
		   rvt_max_atomic(&to_idev(qp->ibqp.device)->rdi),
		   /* remote QP info  */
		   qp->remote_qpn,
		   rdma_ah_get_dlid(&qp->remote_ah_attr),
		   rdma_ah_get_sl(&qp->remote_ah_attr),
		   qp->pmtu,
		   qp->s_retry,
		   qp->s_retry_cnt,
		   qp->s_rnr_retry_cnt,
		   qp->s_rnr_retry,
		   sde,
		   sde ? sde->this_idx : 0,
		   send_context,
		   send_context ? send_context->sw_index : 0,
		   ib_cq_head(qp->ibqp.send_cq),
		   ib_cq_tail(qp->ibqp.send_cq),
		   qp->pid,
		   qp->s_state,
		   qp->s_ack_state,
		   /* ack queue information */
		   e ? e->opcode : 0,
		   e ? e->psn : 0,
		   e ? e->lpsn : 0,
		   qp->r_min_rnr_timer,
		   srq ? "SRQ" : "RQ",
		   srq ? srq->rq.size : qp->r_rq.size
		);
}