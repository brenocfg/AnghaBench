#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_6__ {int pc; int wqe_cnt; int /*<<< orphan*/ * wqe_head; } ;
struct TYPE_5__ {int qpn; } ;
struct TYPE_4__ {int /*<<< orphan*/  sq; } ;
struct mlx5dr_qp {TYPE_3__ sq; TYPE_2__ mqp; TYPE_1__ wq; } ;
struct mlx5_wqe_raddr_seg {scalar_t__ reserved; void* rkey; void* raddr; } ;
struct mlx5_wqe_data_seg {void* addr; void* lkey; void* byte_count; } ;
struct mlx5_wqe_ctrl_seg {void* qpn_ds; void* opmod_idx_opcode; int /*<<< orphan*/  fm_ce_se; scalar_t__ imm; } ;
struct dr_data_seg {int length; int lkey; int /*<<< orphan*/  addr; scalar_t__ send_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_WQE_CTRL_CQ_UPDATE ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_cmd_notify_hw (struct mlx5dr_qp*,struct mlx5_wqe_ctrl_seg*) ; 
 struct mlx5_wqe_ctrl_seg* mlx5_wq_cyc_get_wqe (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void dr_rdma_segments(struct mlx5dr_qp *dr_qp, u64 remote_addr,
			     u32 rkey, struct dr_data_seg *data_seg,
			     u32 opcode, int nreq)
{
	struct mlx5_wqe_raddr_seg *wq_raddr;
	struct mlx5_wqe_ctrl_seg *wq_ctrl;
	struct mlx5_wqe_data_seg *wq_dseg;
	unsigned int size;
	unsigned int idx;

	size = sizeof(*wq_ctrl) / 16 + sizeof(*wq_dseg) / 16 +
		sizeof(*wq_raddr) / 16;

	idx = dr_qp->sq.pc & (dr_qp->sq.wqe_cnt - 1);

	wq_ctrl = mlx5_wq_cyc_get_wqe(&dr_qp->wq.sq, idx);
	wq_ctrl->imm = 0;
	wq_ctrl->fm_ce_se = (data_seg->send_flags) ?
		MLX5_WQE_CTRL_CQ_UPDATE : 0;
	wq_ctrl->opmod_idx_opcode = cpu_to_be32(((dr_qp->sq.pc & 0xffff) << 8) |
						opcode);
	wq_ctrl->qpn_ds = cpu_to_be32(size | dr_qp->mqp.qpn << 8);
	wq_raddr = (void *)(wq_ctrl + 1);
	wq_raddr->raddr = cpu_to_be64(remote_addr);
	wq_raddr->rkey = cpu_to_be32(rkey);
	wq_raddr->reserved = 0;

	wq_dseg = (void *)(wq_raddr + 1);
	wq_dseg->byte_count = cpu_to_be32(data_seg->length);
	wq_dseg->lkey = cpu_to_be32(data_seg->lkey);
	wq_dseg->addr = cpu_to_be64(data_seg->addr);

	dr_qp->sq.wqe_head[idx] = dr_qp->sq.pc++;

	if (nreq)
		dr_cmd_notify_hw(dr_qp, wq_ctrl);
}