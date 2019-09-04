#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rdma_sq_rdma_wqe_2nd {int /*<<< orphan*/  remote_va; int /*<<< orphan*/  r_key; } ;
struct rdma_sq_rdma_wqe_1st {int /*<<< orphan*/  wqe_size; int /*<<< orphan*/  flags; } ;
struct qedr_qp {int dummy; } ;
struct qedr_dev {int dummy; } ;
struct ib_send_wr {int send_flags; scalar_t__ opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  rkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IB_SEND_INLINE ; 
 scalar_t__ IB_WR_RDMA_WRITE ; 
 scalar_t__ IB_WR_RDMA_WRITE_WITH_IMM ; 
 int /*<<< orphan*/  RDMA_SQ_RDMA_WQE_1ST_INLINE_FLG ; 
 int /*<<< orphan*/  SET_FIELD2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedr_prepare_sq_inline_data (struct qedr_dev*,struct qedr_qp*,int /*<<< orphan*/ *,struct ib_send_wr const*,struct ib_send_wr const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedr_prepare_sq_sges (struct qedr_qp*,int /*<<< orphan*/ *,struct ib_send_wr const*) ; 
 TYPE_1__* rdma_wr (struct ib_send_wr const*) ; 

__attribute__((used)) static u32 qedr_prepare_sq_rdma_data(struct qedr_dev *dev,
				     struct qedr_qp *qp,
				     struct rdma_sq_rdma_wqe_1st *rwqe,
				     struct rdma_sq_rdma_wqe_2nd *rwqe2,
				     const struct ib_send_wr *wr,
				     const struct ib_send_wr **bad_wr)
{
	rwqe2->r_key = cpu_to_le32(rdma_wr(wr)->rkey);
	DMA_REGPAIR_LE(rwqe2->remote_va, rdma_wr(wr)->remote_addr);

	if (wr->send_flags & IB_SEND_INLINE &&
	    (wr->opcode == IB_WR_RDMA_WRITE_WITH_IMM ||
	     wr->opcode == IB_WR_RDMA_WRITE)) {
		u8 flags = 0;

		SET_FIELD2(flags, RDMA_SQ_RDMA_WQE_1ST_INLINE_FLG, 1);
		return qedr_prepare_sq_inline_data(dev, qp, &rwqe->wqe_size, wr,
						   bad_wr, &rwqe->flags, flags);
	}

	return qedr_prepare_sq_sges(qp, &rwqe->wqe_size, wr);
}