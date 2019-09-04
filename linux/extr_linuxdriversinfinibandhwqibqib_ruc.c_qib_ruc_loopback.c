#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wc ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_25__ {int /*<<< orphan*/  imm_data; } ;
struct TYPE_17__ {int num_sge; int opcode; int send_flags; TYPE_3__ ex; } ;
struct TYPE_27__ {int const opcode; } ;
struct TYPE_28__ {int /*<<< orphan*/  swap; TYPE_5__ wr; scalar_t__ compare_add; int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_26__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct rvt_swqe {int length; TYPE_10__ wr; TYPE_6__ atomic_wr; struct rvt_sge* sg_list; TYPE_4__ rdma_wr; } ;
struct rvt_sge {scalar_t__ length; scalar_t__ sge_length; scalar_t__ n; scalar_t__ m; TYPE_14__* mr; scalar_t__ vaddr; } ;
struct TYPE_19__ {scalar_t__ qp_type; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; int /*<<< orphan*/  recv_cq; } ;
struct TYPE_20__ {int num_sge; int total_len; struct rvt_sge sge; struct rvt_sge* sg_list; } ;
struct TYPE_29__ {int num_sge; struct rvt_sge* sg_list; struct rvt_sge sge; } ;
struct rvt_qp {int s_flags; size_t state; scalar_t__ s_last; scalar_t__ s_cur; scalar_t__ s_size; int s_len; int r_len; int qp_access_flags; scalar_t__ s_rnr_retry; scalar_t__ s_rnr_retry_cnt; int r_min_rnr_timer; int /*<<< orphan*/  s_lock; TYPE_12__ ibqp; int /*<<< orphan*/  remote_ah_attr; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  r_wr_id; int /*<<< orphan*/  r_aflags; TYPE_13__ r_sge; TYPE_7__ s_sge; int /*<<< orphan*/  s_head; int /*<<< orphan*/  port_num; } ;
struct rvt_dev_info {int dummy; } ;
struct qib_pportdata {struct qib_devdata* dd; } ;
struct TYPE_22__ {int /*<<< orphan*/  n_rnr_naks; int /*<<< orphan*/  n_loop_pkts; int /*<<< orphan*/  n_pkt_drops; } ;
struct qib_ibport {TYPE_15__ rvp; } ;
struct TYPE_23__ {struct rvt_dev_info rdi; } ;
struct qib_devdata {TYPE_1__ verbs_dev; } ;
struct TYPE_24__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {int byte_len; int port_num; void* status; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; int /*<<< orphan*/  src_qp; TYPE_12__* qp; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  opcode; TYPE_2__ ex; void* wc_flags; } ;
struct TYPE_18__ {TYPE_12__* qp; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_11__ element; int /*<<< orphan*/  device; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
typedef  int /*<<< orphan*/  atomic64_t ;
struct TYPE_31__ {TYPE_8__* segs; } ;
struct TYPE_30__ {scalar_t__ length; scalar_t__ vaddr; } ;
struct TYPE_21__ {scalar_t__ mapsz; TYPE_9__** map; scalar_t__ lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int IB_AETH_CREDIT_SHIFT ; 
 int /*<<< orphan*/  IB_EVENT_QP_LAST_WQE_REACHED ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 int IB_SEND_SOLICITED ; 
 void* IB_WC_LOC_PROT_ERR ; 
 void* IB_WC_LOC_QP_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int /*<<< orphan*/  IB_WC_RECV_RDMA_WITH_IMM ; 
 int IB_WC_REM_ACCESS_ERR ; 
 void* IB_WC_REM_INV_REQ_ERR ; 
 int IB_WC_REM_OP_ERR ; 
 int IB_WC_RETRY_EXC_ERR ; 
 int IB_WC_RNR_RETRY_EXC_ERR ; 
 void* IB_WC_SUCCESS ; 
 void* IB_WC_WITH_IMM ; 
 int IB_WC_WR_FLUSH_ERR ; 
#define  IB_WR_ATOMIC_CMP_AND_SWP 134 
#define  IB_WR_ATOMIC_FETCH_AND_ADD 133 
#define  IB_WR_RDMA_READ 132 
#define  IB_WR_RDMA_WRITE 131 
#define  IB_WR_RDMA_WRITE_WITH_IMM 130 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_IMM 128 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int RVT_FLUSH_SEND ; 
 int RVT_PROCESS_NEXT_SEND_OK ; 
 int RVT_PROCESS_OR_FLUSH_SEND ; 
 int RVT_PROCESS_RECV_OK ; 
 int /*<<< orphan*/  RVT_R_WRID_VALID ; 
 scalar_t__ RVT_SEGSZ ; 
 int RVT_S_ANY_WAIT ; 
 int RVT_S_BUSY ; 
 int /*<<< orphan*/  atomic64_add_return (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmpxchg (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/  ibcq_to_rvtcq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_copy_sge (TYPE_13__*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  qib_send_complete (struct rvt_qp*,struct rvt_swqe*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdma_ah_get_dlid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_ah_get_sl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_add_rnr_timer (struct rvt_qp*,int) ; 
 int /*<<< orphan*/  rvt_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int) ; 
 int rvt_error_qp (struct rvt_qp*,int) ; 
 int rvt_get_rwqe (struct rvt_qp*,int) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 struct rvt_qp* rvt_lookup_qpn (struct rvt_dev_info*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_put_mr (TYPE_14__*) ; 
 int /*<<< orphan*/  rvt_put_ss (TYPE_13__*) ; 
 int /*<<< orphan*/  rvt_rc_error (struct rvt_qp*,void*) ; 
 int /*<<< orphan*/  rvt_rkey_ok (struct rvt_qp*,struct rvt_sge*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static void qib_ruc_loopback(struct rvt_qp *sqp)
{
	struct qib_ibport *ibp = to_iport(sqp->ibqp.device, sqp->port_num);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	struct qib_devdata *dd = ppd->dd;
	struct rvt_dev_info *rdi = &dd->verbs_dev.rdi;
	struct rvt_qp *qp;
	struct rvt_swqe *wqe;
	struct rvt_sge *sge;
	unsigned long flags;
	struct ib_wc wc;
	u64 sdata;
	atomic64_t *maddr;
	enum ib_wc_status send_status;
	int release;
	int ret;

	rcu_read_lock();
	/*
	 * Note that we check the responder QP state after
	 * checking the requester's state.
	 */
	qp = rvt_lookup_qpn(rdi, &ibp->rvp, sqp->remote_qpn);
	if (!qp)
		goto done;

	spin_lock_irqsave(&sqp->s_lock, flags);

	/* Return if we are already busy processing a work request. */
	if ((sqp->s_flags & (RVT_S_BUSY | RVT_S_ANY_WAIT)) ||
	    !(ib_rvt_state_ops[sqp->state] & RVT_PROCESS_OR_FLUSH_SEND))
		goto unlock;

	sqp->s_flags |= RVT_S_BUSY;

again:
	if (sqp->s_last == READ_ONCE(sqp->s_head))
		goto clr_busy;
	wqe = rvt_get_swqe_ptr(sqp, sqp->s_last);

	/* Return if it is not OK to start a new work reqeust. */
	if (!(ib_rvt_state_ops[sqp->state] & RVT_PROCESS_NEXT_SEND_OK)) {
		if (!(ib_rvt_state_ops[sqp->state] & RVT_FLUSH_SEND))
			goto clr_busy;
		/* We are in the error state, flush the work request. */
		send_status = IB_WC_WR_FLUSH_ERR;
		goto flush_send;
	}

	/*
	 * We can rely on the entry not changing without the s_lock
	 * being held until we update s_last.
	 * We increment s_cur to indicate s_last is in progress.
	 */
	if (sqp->s_last == sqp->s_cur) {
		if (++sqp->s_cur >= sqp->s_size)
			sqp->s_cur = 0;
	}
	spin_unlock_irqrestore(&sqp->s_lock, flags);

	if (!qp || !(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) ||
	    qp->ibqp.qp_type != sqp->ibqp.qp_type) {
		ibp->rvp.n_pkt_drops++;
		/*
		 * For RC, the requester would timeout and retry so
		 * shortcut the timeouts and just signal too many retries.
		 */
		if (sqp->ibqp.qp_type == IB_QPT_RC)
			send_status = IB_WC_RETRY_EXC_ERR;
		else
			send_status = IB_WC_SUCCESS;
		goto serr;
	}

	memset(&wc, 0, sizeof(wc));
	send_status = IB_WC_SUCCESS;

	release = 1;
	sqp->s_sge.sge = wqe->sg_list[0];
	sqp->s_sge.sg_list = wqe->sg_list + 1;
	sqp->s_sge.num_sge = wqe->wr.num_sge;
	sqp->s_len = wqe->length;
	switch (wqe->wr.opcode) {
	case IB_WR_SEND_WITH_IMM:
		wc.wc_flags = IB_WC_WITH_IMM;
		wc.ex.imm_data = wqe->wr.ex.imm_data;
		/* FALLTHROUGH */
	case IB_WR_SEND:
		ret = rvt_get_rwqe(qp, false);
		if (ret < 0)
			goto op_err;
		if (!ret)
			goto rnr_nak;
		if (wqe->length > qp->r_len)
			goto inv_err;
		break;

	case IB_WR_RDMA_WRITE_WITH_IMM:
		if (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_WRITE)))
			goto inv_err;
		wc.wc_flags = IB_WC_WITH_IMM;
		wc.ex.imm_data = wqe->wr.ex.imm_data;
		ret = rvt_get_rwqe(qp, true);
		if (ret < 0)
			goto op_err;
		if (!ret)
			goto rnr_nak;
		/* FALLTHROUGH */
	case IB_WR_RDMA_WRITE:
		if (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_WRITE)))
			goto inv_err;
		if (wqe->length == 0)
			break;
		if (unlikely(!rvt_rkey_ok(qp, &qp->r_sge.sge, wqe->length,
					  wqe->rdma_wr.remote_addr,
					  wqe->rdma_wr.rkey,
					  IB_ACCESS_REMOTE_WRITE)))
			goto acc_err;
		qp->r_sge.sg_list = NULL;
		qp->r_sge.num_sge = 1;
		qp->r_sge.total_len = wqe->length;
		break;

	case IB_WR_RDMA_READ:
		if (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_READ)))
			goto inv_err;
		if (unlikely(!rvt_rkey_ok(qp, &sqp->s_sge.sge, wqe->length,
					  wqe->rdma_wr.remote_addr,
					  wqe->rdma_wr.rkey,
					  IB_ACCESS_REMOTE_READ)))
			goto acc_err;
		release = 0;
		sqp->s_sge.sg_list = NULL;
		sqp->s_sge.num_sge = 1;
		qp->r_sge.sge = wqe->sg_list[0];
		qp->r_sge.sg_list = wqe->sg_list + 1;
		qp->r_sge.num_sge = wqe->wr.num_sge;
		qp->r_sge.total_len = wqe->length;
		break;

	case IB_WR_ATOMIC_CMP_AND_SWP:
	case IB_WR_ATOMIC_FETCH_AND_ADD:
		if (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_ATOMIC)))
			goto inv_err;
		if (unlikely(!rvt_rkey_ok(qp, &qp->r_sge.sge, sizeof(u64),
					  wqe->atomic_wr.remote_addr,
					  wqe->atomic_wr.rkey,
					  IB_ACCESS_REMOTE_ATOMIC)))
			goto acc_err;
		/* Perform atomic OP and save result. */
		maddr = (atomic64_t *) qp->r_sge.sge.vaddr;
		sdata = wqe->atomic_wr.compare_add;
		*(u64 *) sqp->s_sge.sge.vaddr =
			(wqe->atomic_wr.wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) ?
			(u64) atomic64_add_return(sdata, maddr) - sdata :
			(u64) cmpxchg((u64 *) qp->r_sge.sge.vaddr,
				      sdata, wqe->atomic_wr.swap);
		rvt_put_mr(qp->r_sge.sge.mr);
		qp->r_sge.num_sge = 0;
		goto send_comp;

	default:
		send_status = IB_WC_LOC_QP_OP_ERR;
		goto serr;
	}

	sge = &sqp->s_sge.sge;
	while (sqp->s_len) {
		u32 len = sqp->s_len;

		if (len > sge->length)
			len = sge->length;
		if (len > sge->sge_length)
			len = sge->sge_length;
		BUG_ON(len == 0);
		qib_copy_sge(&qp->r_sge, sge->vaddr, len, release);
		sge->vaddr += len;
		sge->length -= len;
		sge->sge_length -= len;
		if (sge->sge_length == 0) {
			if (!release)
				rvt_put_mr(sge->mr);
			if (--sqp->s_sge.num_sge)
				*sge = *sqp->s_sge.sg_list++;
		} else if (sge->length == 0 && sge->mr->lkey) {
			if (++sge->n >= RVT_SEGSZ) {
				if (++sge->m >= sge->mr->mapsz)
					break;
				sge->n = 0;
			}
			sge->vaddr =
				sge->mr->map[sge->m]->segs[sge->n].vaddr;
			sge->length =
				sge->mr->map[sge->m]->segs[sge->n].length;
		}
		sqp->s_len -= len;
	}
	if (release)
		rvt_put_ss(&qp->r_sge);

	if (!test_and_clear_bit(RVT_R_WRID_VALID, &qp->r_aflags))
		goto send_comp;

	if (wqe->wr.opcode == IB_WR_RDMA_WRITE_WITH_IMM)
		wc.opcode = IB_WC_RECV_RDMA_WITH_IMM;
	else
		wc.opcode = IB_WC_RECV;
	wc.wr_id = qp->r_wr_id;
	wc.status = IB_WC_SUCCESS;
	wc.byte_len = wqe->length;
	wc.qp = &qp->ibqp;
	wc.src_qp = qp->remote_qpn;
	wc.slid = rdma_ah_get_dlid(&qp->remote_ah_attr);
	wc.sl = rdma_ah_get_sl(&qp->remote_ah_attr);
	wc.port_num = 1;
	/* Signal completion event if the solicited bit is set. */
	rvt_cq_enter(ibcq_to_rvtcq(qp->ibqp.recv_cq), &wc,
		     wqe->wr.send_flags & IB_SEND_SOLICITED);

send_comp:
	spin_lock_irqsave(&sqp->s_lock, flags);
	ibp->rvp.n_loop_pkts++;
flush_send:
	sqp->s_rnr_retry = sqp->s_rnr_retry_cnt;
	qib_send_complete(sqp, wqe, send_status);
	goto again;

rnr_nak:
	/* Handle RNR NAK */
	if (qp->ibqp.qp_type == IB_QPT_UC)
		goto send_comp;
	ibp->rvp.n_rnr_naks++;
	/*
	 * Note: we don't need the s_lock held since the BUSY flag
	 * makes this single threaded.
	 */
	if (sqp->s_rnr_retry == 0) {
		send_status = IB_WC_RNR_RETRY_EXC_ERR;
		goto serr;
	}
	if (sqp->s_rnr_retry_cnt < 7)
		sqp->s_rnr_retry--;
	spin_lock_irqsave(&sqp->s_lock, flags);
	if (!(ib_rvt_state_ops[sqp->state] & RVT_PROCESS_RECV_OK))
		goto clr_busy;
	rvt_add_rnr_timer(sqp, qp->r_min_rnr_timer <<
				IB_AETH_CREDIT_SHIFT);
	goto clr_busy;

op_err:
	send_status = IB_WC_REM_OP_ERR;
	wc.status = IB_WC_LOC_QP_OP_ERR;
	goto err;

inv_err:
	send_status =
		sqp->ibqp.qp_type == IB_QPT_RC ?
			IB_WC_REM_INV_REQ_ERR :
			IB_WC_SUCCESS;
	wc.status = IB_WC_LOC_QP_OP_ERR;
	goto err;

acc_err:
	send_status = IB_WC_REM_ACCESS_ERR;
	wc.status = IB_WC_LOC_PROT_ERR;
err:
	/* responder goes to error state */
	rvt_rc_error(qp, wc.status);

serr:
	spin_lock_irqsave(&sqp->s_lock, flags);
	qib_send_complete(sqp, wqe, send_status);
	if (sqp->ibqp.qp_type == IB_QPT_RC) {
		int lastwqe = rvt_error_qp(sqp, IB_WC_WR_FLUSH_ERR);

		sqp->s_flags &= ~RVT_S_BUSY;
		spin_unlock_irqrestore(&sqp->s_lock, flags);
		if (lastwqe) {
			struct ib_event ev;

			ev.device = sqp->ibqp.device;
			ev.element.qp = &sqp->ibqp;
			ev.event = IB_EVENT_QP_LAST_WQE_REACHED;
			sqp->ibqp.event_handler(&ev, sqp->ibqp.qp_context);
		}
		goto done;
	}
clr_busy:
	sqp->s_flags &= ~RVT_S_BUSY;
unlock:
	spin_unlock_irqrestore(&sqp->s_lock, flags);
done:
	rcu_read_unlock();
}