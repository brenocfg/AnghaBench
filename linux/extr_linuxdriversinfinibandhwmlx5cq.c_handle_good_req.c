#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_ib_wq {int dummy; } ;
struct mlx5_cqe64 {int /*<<< orphan*/  byte_cnt; int /*<<< orphan*/  sop_drop_qpn; } ;
struct ib_wc {int byte_len; int /*<<< orphan*/  opcode; scalar_t__ wc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_COMP_SWAP ; 
 int /*<<< orphan*/  IB_WC_FETCH_ADD ; 
 int /*<<< orphan*/  IB_WC_MASKED_COMP_SWAP ; 
 int /*<<< orphan*/  IB_WC_MASKED_FETCH_ADD ; 
 int /*<<< orphan*/  IB_WC_RDMA_READ ; 
 int /*<<< orphan*/  IB_WC_RDMA_WRITE ; 
 int /*<<< orphan*/  IB_WC_SEND ; 
 scalar_t__ IB_WC_WITH_IMM ; 
#define  MLX5_OPCODE_ATOMIC_CS 138 
#define  MLX5_OPCODE_ATOMIC_FA 137 
#define  MLX5_OPCODE_ATOMIC_MASKED_CS 136 
#define  MLX5_OPCODE_ATOMIC_MASKED_FA 135 
#define  MLX5_OPCODE_RDMA_READ 134 
#define  MLX5_OPCODE_RDMA_WRITE 133 
#define  MLX5_OPCODE_RDMA_WRITE_IMM 132 
#define  MLX5_OPCODE_SEND 131 
#define  MLX5_OPCODE_SEND_IMM 130 
#define  MLX5_OPCODE_SEND_INVAL 129 
#define  MLX5_OPCODE_UMR 128 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_umr_comp (struct mlx5_ib_wq*,int) ; 

__attribute__((used)) static void handle_good_req(struct ib_wc *wc, struct mlx5_cqe64 *cqe,
			    struct mlx5_ib_wq *wq, int idx)
{
	wc->wc_flags = 0;
	switch (be32_to_cpu(cqe->sop_drop_qpn) >> 24) {
	case MLX5_OPCODE_RDMA_WRITE_IMM:
		wc->wc_flags |= IB_WC_WITH_IMM;
		/* fall through */
	case MLX5_OPCODE_RDMA_WRITE:
		wc->opcode    = IB_WC_RDMA_WRITE;
		break;
	case MLX5_OPCODE_SEND_IMM:
		wc->wc_flags |= IB_WC_WITH_IMM;
		/* fall through */
	case MLX5_OPCODE_SEND:
	case MLX5_OPCODE_SEND_INVAL:
		wc->opcode    = IB_WC_SEND;
		break;
	case MLX5_OPCODE_RDMA_READ:
		wc->opcode    = IB_WC_RDMA_READ;
		wc->byte_len  = be32_to_cpu(cqe->byte_cnt);
		break;
	case MLX5_OPCODE_ATOMIC_CS:
		wc->opcode    = IB_WC_COMP_SWAP;
		wc->byte_len  = 8;
		break;
	case MLX5_OPCODE_ATOMIC_FA:
		wc->opcode    = IB_WC_FETCH_ADD;
		wc->byte_len  = 8;
		break;
	case MLX5_OPCODE_ATOMIC_MASKED_CS:
		wc->opcode    = IB_WC_MASKED_COMP_SWAP;
		wc->byte_len  = 8;
		break;
	case MLX5_OPCODE_ATOMIC_MASKED_FA:
		wc->opcode    = IB_WC_MASKED_FETCH_ADD;
		wc->byte_len  = 8;
		break;
	case MLX5_OPCODE_UMR:
		wc->opcode = get_umr_comp(wq, idx);
		break;
	}
}