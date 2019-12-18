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
struct TYPE_7__ {scalar_t__ imm_data; } ;
struct ib_wc {int vendor_err; int /*<<< orphan*/  byte_len; int /*<<< orphan*/  src_qp; struct ib_qp* qp; TYPE_3__ ex; void* opcode; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; scalar_t__ wc_flags; } ;
struct ib_qp {int dummy; } ;
struct ib_cq {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  rq_ring; int /*<<< orphan*/  sq_ring; } ;
struct i40iw_sc_qp {TYPE_4__ qp_uk; scalar_t__ back_qp; } ;
struct i40iw_qp {scalar_t__ iwarp_state; int /*<<< orphan*/  rq_drained; int /*<<< orphan*/  sq_drained; } ;
struct TYPE_6__ {int (* iw_cq_poll_completion ) (struct i40iw_cq_uk*,struct i40iw_cq_poll_info*) ;} ;
struct i40iw_cq_uk {TYPE_2__ ops; } ;
struct i40iw_cq_poll_info {int major_err; int minor_err; int op_type; int /*<<< orphan*/  bytes_xfered; int /*<<< orphan*/  qp_id; scalar_t__ qp_handle; scalar_t__ error; int /*<<< orphan*/  wr_id; } ;
struct TYPE_5__ {struct i40iw_cq_uk cq_uk; } ;
struct i40iw_cq {int /*<<< orphan*/  lock; TYPE_1__ sc_cq; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_QUEUE_DESTROYED ; 
 int I40IW_ERR_QUEUE_EMPTY ; 
#define  I40IW_OP_TYPE_RDMA_READ 135 
#define  I40IW_OP_TYPE_RDMA_READ_INV_STAG 134 
#define  I40IW_OP_TYPE_RDMA_WRITE 133 
#define  I40IW_OP_TYPE_REC 132 
#define  I40IW_OP_TYPE_SEND 131 
#define  I40IW_OP_TYPE_SEND_INV 130 
#define  I40IW_OP_TYPE_SEND_SOL 129 
#define  I40IW_OP_TYPE_SEND_SOL_INV 128 
 scalar_t__ I40IW_QP_STATE_RTS ; 
 int /*<<< orphan*/  I40IW_RING_MORE_WORK (int /*<<< orphan*/ ) ; 
 void* IB_WC_RDMA_READ ; 
 void* IB_WC_RDMA_WRITE ; 
 void* IB_WC_RECV ; 
 void* IB_WC_SEND ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct i40iw_cq_uk*,struct i40iw_cq_poll_info*) ; 

__attribute__((used)) static int i40iw_poll_cq(struct ib_cq *ibcq,
			 int num_entries,
			 struct ib_wc *entry)
{
	struct i40iw_cq *iwcq;
	int cqe_count = 0;
	struct i40iw_cq_poll_info cq_poll_info;
	enum i40iw_status_code ret;
	struct i40iw_cq_uk *ukcq;
	struct i40iw_sc_qp *qp;
	struct i40iw_qp *iwqp;
	unsigned long flags;

	iwcq = (struct i40iw_cq *)ibcq;
	ukcq = &iwcq->sc_cq.cq_uk;

	spin_lock_irqsave(&iwcq->lock, flags);
	while (cqe_count < num_entries) {
		ret = ukcq->ops.iw_cq_poll_completion(ukcq, &cq_poll_info);
		if (ret == I40IW_ERR_QUEUE_EMPTY) {
			break;
		} else if (ret == I40IW_ERR_QUEUE_DESTROYED) {
			continue;
		} else if (ret) {
			if (!cqe_count)
				cqe_count = -1;
			break;
		}
		entry->wc_flags = 0;
		entry->wr_id = cq_poll_info.wr_id;
		if (cq_poll_info.error) {
			entry->status = IB_WC_WR_FLUSH_ERR;
			entry->vendor_err = cq_poll_info.major_err << 16 | cq_poll_info.minor_err;
		} else {
			entry->status = IB_WC_SUCCESS;
		}

		switch (cq_poll_info.op_type) {
		case I40IW_OP_TYPE_RDMA_WRITE:
			entry->opcode = IB_WC_RDMA_WRITE;
			break;
		case I40IW_OP_TYPE_RDMA_READ_INV_STAG:
		case I40IW_OP_TYPE_RDMA_READ:
			entry->opcode = IB_WC_RDMA_READ;
			break;
		case I40IW_OP_TYPE_SEND_SOL:
		case I40IW_OP_TYPE_SEND_SOL_INV:
		case I40IW_OP_TYPE_SEND_INV:
		case I40IW_OP_TYPE_SEND:
			entry->opcode = IB_WC_SEND;
			break;
		case I40IW_OP_TYPE_REC:
			entry->opcode = IB_WC_RECV;
			break;
		default:
			entry->opcode = IB_WC_RECV;
			break;
		}

		entry->ex.imm_data = 0;
		qp = (struct i40iw_sc_qp *)cq_poll_info.qp_handle;
		entry->qp = (struct ib_qp *)qp->back_qp;
		entry->src_qp = cq_poll_info.qp_id;
		iwqp = (struct i40iw_qp *)qp->back_qp;
		if (iwqp->iwarp_state > I40IW_QP_STATE_RTS) {
			if (!I40IW_RING_MORE_WORK(qp->qp_uk.sq_ring))
				complete(&iwqp->sq_drained);
			if (!I40IW_RING_MORE_WORK(qp->qp_uk.rq_ring))
				complete(&iwqp->rq_drained);
		}
		entry->byte_len = cq_poll_info.bytes_xfered;
		entry++;
		cqe_count++;
	}
	spin_unlock_irqrestore(&iwcq->lock, flags);
	return cqe_count;
}