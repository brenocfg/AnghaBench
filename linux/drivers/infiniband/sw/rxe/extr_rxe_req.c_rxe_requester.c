#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_14__ {int resid; } ;
struct TYPE_18__ {TYPE_10__* mr; int /*<<< orphan*/  key; int /*<<< orphan*/  access; } ;
struct TYPE_19__ {TYPE_5__ reg; } ;
struct TYPE_17__ {int invalidate_rkey; } ;
struct TYPE_20__ {int send_flags; int /*<<< orphan*/  opcode; TYPE_6__ wr; TYPE_4__ ex; } ;
struct rxe_send_wqe {int mask; scalar_t__ first_psn; scalar_t__ last_psn; void* state; void* status; TYPE_1__ dma; TYPE_7__ wr; } ;
struct TYPE_21__ {scalar_t__ psn; int /*<<< orphan*/  task; } ;
struct TYPE_22__ {scalar_t__ state; int opcode; int wait_psn; int need_retry; scalar_t__ psn; int /*<<< orphan*/  task; void* wqe_index; scalar_t__ need_rd_atomic; } ;
struct TYPE_15__ {int /*<<< orphan*/  queue; } ;
struct TYPE_16__ {int /*<<< orphan*/  device; } ;
struct rxe_qp {scalar_t__ sq_sig_type; int need_req_skb; TYPE_8__ comp; TYPE_9__ req; TYPE_2__ sq; int /*<<< orphan*/  skb_out; int /*<<< orphan*/  iova; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; int /*<<< orphan*/  access; int /*<<< orphan*/  state; TYPE_3__ ibqp; int /*<<< orphan*/  valid; } ;
struct rxe_pkt_info {int dummy; } ;
struct rxe_mem {scalar_t__ sq_sig_type; int need_req_skb; TYPE_8__ comp; TYPE_9__ req; TYPE_2__ sq; int /*<<< orphan*/  skb_out; int /*<<< orphan*/  iova; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; int /*<<< orphan*/  access; int /*<<< orphan*/  state; TYPE_3__ ibqp; int /*<<< orphan*/  valid; } ;
struct rxe_dev {int /*<<< orphan*/  mr_pool; } ;
typedef  enum rxe_hdr_mask { ____Placeholder_rxe_hdr_mask } rxe_hdr_mask ;
struct TYPE_13__ {int mask; } ;
struct TYPE_12__ {int /*<<< orphan*/  iova; } ;

/* Variables and functions */
 int BTH_PSN_MASK ; 
 int EAGAIN ; 
 int IB_OPCODE_UD_SEND_ONLY ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UD ; 
 int IB_SEND_SIGNALED ; 
 scalar_t__ IB_SIGNAL_ALL_WR ; 
 void* IB_WC_LOC_PROT_ERR ; 
 void* IB_WC_LOC_QP_OP_ERR ; 
 void* IB_WC_MW_BIND_ERR ; 
 void* IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WR_LOCAL_INV ; 
 int /*<<< orphan*/  IB_WR_REG_MR ; 
 scalar_t__ QP_STATE_ERROR ; 
 scalar_t__ QP_STATE_RESET ; 
 scalar_t__ RXE_INFLIGHT_SKBS_PER_QP_HIGH ; 
 scalar_t__ RXE_MAX_UNACKED_PSNS ; 
 int /*<<< orphan*/  RXE_MEM_STATE_FREE ; 
 int /*<<< orphan*/  RXE_MEM_STATE_VALID ; 
 int RXE_READ_OR_ATOMIC ; 
 int RXE_WRITE_OR_SEND ; 
 int WR_REG_MASK ; 
 int /*<<< orphan*/  __rxe_do_task (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ check_init_depth (struct rxe_qp*,struct rxe_send_wqe*) ; 
 void* consumer_index (int /*<<< orphan*/ ) ; 
 scalar_t__ fill_packet (struct rxe_qp*,struct rxe_send_wqe*,struct rxe_pkt_info*,struct sk_buff*,int) ; 
 int get_mtu (struct rxe_qp*) ; 
 struct sk_buff* init_req_packet (struct rxe_qp*,struct rxe_send_wqe*,int,int,struct rxe_pkt_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* next_index (int /*<<< orphan*/ ,void*) ; 
 int next_opcode (struct rxe_qp*,struct rxe_send_wqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int qp_num (struct rxe_qp*) ; 
 scalar_t__ qp_type (struct rxe_qp*) ; 
 struct rxe_send_wqe* req_next_wqe (struct rxe_qp*) ; 
 int /*<<< orphan*/  req_retry (struct rxe_qp*) ; 
 int /*<<< orphan*/  rollback_state (struct rxe_send_wqe*,struct rxe_qp*,struct rxe_send_wqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_add_ref (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_qp*) ; 
 TYPE_11__* rxe_opcode ; 
 struct rxe_qp* rxe_pool_get_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 
 int rxe_xmit_packet (struct rxe_qp*,struct rxe_pkt_info*,struct sk_buff*) ; 
 int /*<<< orphan*/  save_state (struct rxe_send_wqe*,struct rxe_qp*,struct rxe_send_wqe*,int /*<<< orphan*/ *) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 
 struct rxe_qp* to_rmr (TYPE_10__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_state (struct rxe_qp*,struct rxe_send_wqe*,struct rxe_pkt_info*,int) ; 
 int /*<<< orphan*/  update_wqe_psn (struct rxe_qp*,struct rxe_send_wqe*,struct rxe_pkt_info*,int) ; 
 int /*<<< orphan*/  update_wqe_state (struct rxe_qp*,struct rxe_send_wqe*,struct rxe_pkt_info*) ; 
 void* wqe_state_done ; 
 void* wqe_state_error ; 

int rxe_requester(void *arg)
{
	struct rxe_qp *qp = (struct rxe_qp *)arg;
	struct rxe_pkt_info pkt;
	struct sk_buff *skb;
	struct rxe_send_wqe *wqe;
	enum rxe_hdr_mask mask;
	int payload;
	int mtu;
	int opcode;
	int ret;
	struct rxe_send_wqe rollback_wqe;
	u32 rollback_psn;

	rxe_add_ref(qp);

next_wqe:
	if (unlikely(!qp->valid || qp->req.state == QP_STATE_ERROR))
		goto exit;

	if (unlikely(qp->req.state == QP_STATE_RESET)) {
		qp->req.wqe_index = consumer_index(qp->sq.queue);
		qp->req.opcode = -1;
		qp->req.need_rd_atomic = 0;
		qp->req.wait_psn = 0;
		qp->req.need_retry = 0;
		goto exit;
	}

	if (unlikely(qp->req.need_retry)) {
		req_retry(qp);
		qp->req.need_retry = 0;
	}

	wqe = req_next_wqe(qp);
	if (unlikely(!wqe))
		goto exit;

	if (wqe->mask & WR_REG_MASK) {
		if (wqe->wr.opcode == IB_WR_LOCAL_INV) {
			struct rxe_dev *rxe = to_rdev(qp->ibqp.device);
			struct rxe_mem *rmr;

			rmr = rxe_pool_get_index(&rxe->mr_pool,
						 wqe->wr.ex.invalidate_rkey >> 8);
			if (!rmr) {
				pr_err("No mr for key %#x\n",
				       wqe->wr.ex.invalidate_rkey);
				wqe->state = wqe_state_error;
				wqe->status = IB_WC_MW_BIND_ERR;
				goto exit;
			}
			rmr->state = RXE_MEM_STATE_FREE;
			rxe_drop_ref(rmr);
			wqe->state = wqe_state_done;
			wqe->status = IB_WC_SUCCESS;
		} else if (wqe->wr.opcode == IB_WR_REG_MR) {
			struct rxe_mem *rmr = to_rmr(wqe->wr.wr.reg.mr);

			rmr->state = RXE_MEM_STATE_VALID;
			rmr->access = wqe->wr.wr.reg.access;
			rmr->lkey = wqe->wr.wr.reg.key;
			rmr->rkey = wqe->wr.wr.reg.key;
			rmr->iova = wqe->wr.wr.reg.mr->iova;
			wqe->state = wqe_state_done;
			wqe->status = IB_WC_SUCCESS;
		} else {
			goto exit;
		}
		if ((wqe->wr.send_flags & IB_SEND_SIGNALED) ||
		    qp->sq_sig_type == IB_SIGNAL_ALL_WR)
			rxe_run_task(&qp->comp.task, 1);
		qp->req.wqe_index = next_index(qp->sq.queue,
						qp->req.wqe_index);
		goto next_wqe;
	}

	if (unlikely(qp_type(qp) == IB_QPT_RC &&
		     qp->req.psn > (qp->comp.psn + RXE_MAX_UNACKED_PSNS))) {
		qp->req.wait_psn = 1;
		goto exit;
	}

	/* Limit the number of inflight SKBs per QP */
	if (unlikely(atomic_read(&qp->skb_out) >
		     RXE_INFLIGHT_SKBS_PER_QP_HIGH)) {
		qp->need_req_skb = 1;
		goto exit;
	}

	opcode = next_opcode(qp, wqe, wqe->wr.opcode);
	if (unlikely(opcode < 0)) {
		wqe->status = IB_WC_LOC_QP_OP_ERR;
		goto exit;
	}

	mask = rxe_opcode[opcode].mask;
	if (unlikely(mask & RXE_READ_OR_ATOMIC)) {
		if (check_init_depth(qp, wqe))
			goto exit;
	}

	mtu = get_mtu(qp);
	payload = (mask & RXE_WRITE_OR_SEND) ? wqe->dma.resid : 0;
	if (payload > mtu) {
		if (qp_type(qp) == IB_QPT_UD) {
			/* C10-93.1.1: If the total sum of all the buffer lengths specified for a
			 * UD message exceeds the MTU of the port as returned by QueryHCA, the CI
			 * shall not emit any packets for this message. Further, the CI shall not
			 * generate an error due to this condition.
			 */

			/* fake a successful UD send */
			wqe->first_psn = qp->req.psn;
			wqe->last_psn = qp->req.psn;
			qp->req.psn = (qp->req.psn + 1) & BTH_PSN_MASK;
			qp->req.opcode = IB_OPCODE_UD_SEND_ONLY;
			qp->req.wqe_index = next_index(qp->sq.queue,
						       qp->req.wqe_index);
			wqe->state = wqe_state_done;
			wqe->status = IB_WC_SUCCESS;
			__rxe_do_task(&qp->comp.task);
			rxe_drop_ref(qp);
			return 0;
		}
		payload = mtu;
	}

	skb = init_req_packet(qp, wqe, opcode, payload, &pkt);
	if (unlikely(!skb)) {
		pr_err("qp#%d Failed allocating skb\n", qp_num(qp));
		goto err;
	}

	if (fill_packet(qp, wqe, &pkt, skb, payload)) {
		pr_debug("qp#%d Error during fill packet\n", qp_num(qp));
		kfree_skb(skb);
		goto err;
	}

	/*
	 * To prevent a race on wqe access between requester and completer,
	 * wqe members state and psn need to be set before calling
	 * rxe_xmit_packet().
	 * Otherwise, completer might initiate an unjustified retry flow.
	 */
	save_state(wqe, qp, &rollback_wqe, &rollback_psn);
	update_wqe_state(qp, wqe, &pkt);
	update_wqe_psn(qp, wqe, &pkt, payload);
	ret = rxe_xmit_packet(qp, &pkt, skb);
	if (ret) {
		qp->need_req_skb = 1;

		rollback_state(wqe, qp, &rollback_wqe, rollback_psn);

		if (ret == -EAGAIN) {
			rxe_run_task(&qp->req.task, 1);
			goto exit;
		}

		goto err;
	}

	update_state(qp, wqe, &pkt, payload);

	goto next_wqe;

err:
	wqe->status = IB_WC_LOC_PROT_ERR;
	wqe->state = wqe_state_error;
	__rxe_do_task(&qp->comp.task);

exit:
	rxe_drop_ref(qp);
	return -EAGAIN;
}