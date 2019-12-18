#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ocrdma_sge {int dummy; } ;
struct TYPE_8__ {scalar_t__ max_sges; size_t head; } ;
struct ocrdma_qp {scalar_t__ state; scalar_t__ qp_type; int /*<<< orphan*/  q_lock; TYPE_3__ sq; TYPE_2__* wqe_wr_id_tbl; scalar_t__ signaled; } ;
struct ocrdma_hdr_wqe {int cw; int /*<<< orphan*/  lkey; void* immdt; scalar_t__ total_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  invalidate_rkey; int /*<<< orphan*/  imm_data; } ;
struct ib_send_wr {int opcode; scalar_t__ num_sge; int send_flags; struct ib_send_wr* next; int /*<<< orphan*/  wr_id; TYPE_1__ ex; } ;
struct ib_qp {int dummy; } ;
struct TYPE_7__ {int signaled; int /*<<< orphan*/  wrid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IB_QPT_UD ; 
 int IB_SEND_FENCE ; 
 int IB_SEND_SIGNALED ; 
 int IB_SEND_SOLICITED ; 
#define  IB_WR_LOCAL_INV 135 
#define  IB_WR_RDMA_READ 134 
#define  IB_WR_RDMA_WRITE 133 
#define  IB_WR_RDMA_WRITE_WITH_IMM 132 
#define  IB_WR_REG_MR 131 
#define  IB_WR_SEND 130 
#define  IB_WR_SEND_WITH_IMM 129 
#define  IB_WR_SEND_WITH_INV 128 
 int OCRDMA_FLAG_FENCE_L ; 
 int OCRDMA_FLAG_IMM ; 
 int OCRDMA_FLAG_INV ; 
 int OCRDMA_FLAG_SIG ; 
 int OCRDMA_FLAG_SOLICIT ; 
 int OCRDMA_LKEY_INV ; 
 scalar_t__ OCRDMA_QPS_RTS ; 
 scalar_t__ OCRDMA_QPS_SQD ; 
 int OCRDMA_SEND ; 
 int OCRDMA_WQE_FLAGS_SHIFT ; 
 int OCRDMA_WQE_OPCODE_SHIFT ; 
 int OCRDMA_WQE_SIZE_MASK ; 
 int OCRDMA_WQE_SIZE_SHIFT ; 
 int OCRDMA_WQE_STRIDE ; 
 int OCRDMA_WRITE ; 
 struct ocrdma_qp* get_ocrdma_qp (struct ib_qp*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_build_read (struct ocrdma_qp*,struct ocrdma_hdr_wqe*,struct ib_send_wr const*) ; 
 int ocrdma_build_reg (struct ocrdma_qp*,struct ocrdma_hdr_wqe*,int /*<<< orphan*/ ) ; 
 int ocrdma_build_send (struct ocrdma_qp*,struct ocrdma_hdr_wqe*,struct ib_send_wr const*) ; 
 int ocrdma_build_write (struct ocrdma_qp*,struct ocrdma_hdr_wqe*,struct ib_send_wr const*) ; 
 int /*<<< orphan*/  ocrdma_cpu_to_le32 (struct ocrdma_hdr_wqe*,int) ; 
 scalar_t__ ocrdma_hwq_free_cnt (TYPE_3__*) ; 
 struct ocrdma_hdr_wqe* ocrdma_hwq_head (TYPE_3__*) ; 
 int /*<<< orphan*/  ocrdma_hwq_inc_head (TYPE_3__*) ; 
 int /*<<< orphan*/  ocrdma_ring_sq_db (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  reg_wr (struct ib_send_wr const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

int ocrdma_post_send(struct ib_qp *ibqp, const struct ib_send_wr *wr,
		     const struct ib_send_wr **bad_wr)
{
	int status = 0;
	struct ocrdma_qp *qp = get_ocrdma_qp(ibqp);
	struct ocrdma_hdr_wqe *hdr;
	unsigned long flags;

	spin_lock_irqsave(&qp->q_lock, flags);
	if (qp->state != OCRDMA_QPS_RTS && qp->state != OCRDMA_QPS_SQD) {
		spin_unlock_irqrestore(&qp->q_lock, flags);
		*bad_wr = wr;
		return -EINVAL;
	}

	while (wr) {
		if (qp->qp_type == IB_QPT_UD &&
		    (wr->opcode != IB_WR_SEND &&
		     wr->opcode != IB_WR_SEND_WITH_IMM)) {
			*bad_wr = wr;
			status = -EINVAL;
			break;
		}
		if (ocrdma_hwq_free_cnt(&qp->sq) == 0 ||
		    wr->num_sge > qp->sq.max_sges) {
			*bad_wr = wr;
			status = -ENOMEM;
			break;
		}
		hdr = ocrdma_hwq_head(&qp->sq);
		hdr->cw = 0;
		if (wr->send_flags & IB_SEND_SIGNALED || qp->signaled)
			hdr->cw |= (OCRDMA_FLAG_SIG << OCRDMA_WQE_FLAGS_SHIFT);
		if (wr->send_flags & IB_SEND_FENCE)
			hdr->cw |=
			    (OCRDMA_FLAG_FENCE_L << OCRDMA_WQE_FLAGS_SHIFT);
		if (wr->send_flags & IB_SEND_SOLICITED)
			hdr->cw |=
			    (OCRDMA_FLAG_SOLICIT << OCRDMA_WQE_FLAGS_SHIFT);
		hdr->total_len = 0;
		switch (wr->opcode) {
		case IB_WR_SEND_WITH_IMM:
			hdr->cw |= (OCRDMA_FLAG_IMM << OCRDMA_WQE_FLAGS_SHIFT);
			hdr->immdt = ntohl(wr->ex.imm_data);
			/* fall through */
		case IB_WR_SEND:
			hdr->cw |= (OCRDMA_SEND << OCRDMA_WQE_OPCODE_SHIFT);
			ocrdma_build_send(qp, hdr, wr);
			break;
		case IB_WR_SEND_WITH_INV:
			hdr->cw |= (OCRDMA_FLAG_INV << OCRDMA_WQE_FLAGS_SHIFT);
			hdr->cw |= (OCRDMA_SEND << OCRDMA_WQE_OPCODE_SHIFT);
			hdr->lkey = wr->ex.invalidate_rkey;
			status = ocrdma_build_send(qp, hdr, wr);
			break;
		case IB_WR_RDMA_WRITE_WITH_IMM:
			hdr->cw |= (OCRDMA_FLAG_IMM << OCRDMA_WQE_FLAGS_SHIFT);
			hdr->immdt = ntohl(wr->ex.imm_data);
			/* fall through */
		case IB_WR_RDMA_WRITE:
			hdr->cw |= (OCRDMA_WRITE << OCRDMA_WQE_OPCODE_SHIFT);
			status = ocrdma_build_write(qp, hdr, wr);
			break;
		case IB_WR_RDMA_READ:
			ocrdma_build_read(qp, hdr, wr);
			break;
		case IB_WR_LOCAL_INV:
			hdr->cw |=
			    (OCRDMA_LKEY_INV << OCRDMA_WQE_OPCODE_SHIFT);
			hdr->cw |= ((sizeof(struct ocrdma_hdr_wqe) +
					sizeof(struct ocrdma_sge)) /
				OCRDMA_WQE_STRIDE) << OCRDMA_WQE_SIZE_SHIFT;
			hdr->lkey = wr->ex.invalidate_rkey;
			break;
		case IB_WR_REG_MR:
			status = ocrdma_build_reg(qp, hdr, reg_wr(wr));
			break;
		default:
			status = -EINVAL;
			break;
		}
		if (status) {
			*bad_wr = wr;
			break;
		}
		if (wr->send_flags & IB_SEND_SIGNALED || qp->signaled)
			qp->wqe_wr_id_tbl[qp->sq.head].signaled = 1;
		else
			qp->wqe_wr_id_tbl[qp->sq.head].signaled = 0;
		qp->wqe_wr_id_tbl[qp->sq.head].wrid = wr->wr_id;
		ocrdma_cpu_to_le32(hdr, ((hdr->cw >> OCRDMA_WQE_SIZE_SHIFT) &
				   OCRDMA_WQE_SIZE_MASK) * OCRDMA_WQE_STRIDE);
		/* make sure wqe is written before adapter can access it */
		wmb();
		/* inform hw to start processing it */
		ocrdma_ring_sq_db(qp);

		/* update pointer, counter for next wr */
		ocrdma_hwq_inc_head(&qp->sq);
		wr = wr->next;
	}
	spin_unlock_irqrestore(&qp->q_lock, flags);
	return status;
}