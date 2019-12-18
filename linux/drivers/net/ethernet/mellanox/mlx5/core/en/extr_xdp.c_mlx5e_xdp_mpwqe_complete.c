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
typedef  size_t u16 ;
struct TYPE_3__ {struct mlx5e_xdp_wqe_info* wqe_info; } ;
struct mlx5e_xdp_mpwqe {size_t ds_count; TYPE_2__* wqe; int /*<<< orphan*/  pkt_count; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct mlx5e_xdpsq {int pc; int sqn; struct mlx5_wqe_ctrl_seg* doorbell_cseg; TYPE_1__ db; struct mlx5e_xdp_mpwqe mpwqe; struct mlx5_wq_cyc wq; } ;
struct mlx5e_xdp_wqe_info {scalar_t__ num_wqebbs; int /*<<< orphan*/  num_pkts; } ;
struct mlx5_wqe_ctrl_seg {void* qpn_ds; void* opmod_idx_opcode; } ;
struct TYPE_4__ {struct mlx5_wqe_ctrl_seg ctrl; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (size_t,int /*<<< orphan*/ ) ; 
 int MLX5_OPCODE_ENHANCED_MPSW ; 
 int /*<<< orphan*/  MLX5_SEND_WQEBB_NUM_DS ; 
 void* cpu_to_be32 (int) ; 
 size_t mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int) ; 

void mlx5e_xdp_mpwqe_complete(struct mlx5e_xdpsq *sq)
{
	struct mlx5_wq_cyc       *wq    = &sq->wq;
	struct mlx5e_xdp_mpwqe *session = &sq->mpwqe;
	struct mlx5_wqe_ctrl_seg *cseg = &session->wqe->ctrl;
	u16 ds_count = session->ds_count;
	u16 pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	struct mlx5e_xdp_wqe_info *wi = &sq->db.wqe_info[pi];

	cseg->opmod_idx_opcode =
		cpu_to_be32((sq->pc << 8) | MLX5_OPCODE_ENHANCED_MPSW);
	cseg->qpn_ds = cpu_to_be32((sq->sqn << 8) | ds_count);

	wi->num_wqebbs = DIV_ROUND_UP(ds_count, MLX5_SEND_WQEBB_NUM_DS);
	wi->num_pkts   = session->pkt_count;

	sq->pc += wi->num_wqebbs;

	sq->doorbell_cseg = cseg;

	session->wqe = NULL; /* Close session */
}