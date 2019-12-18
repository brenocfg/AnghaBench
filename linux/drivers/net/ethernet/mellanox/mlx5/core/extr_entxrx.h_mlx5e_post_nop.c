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
typedef  int u32 ;
typedef  int u16 ;
struct mlx5_wqe_ctrl_seg {void* qpn_ds; void* opmod_idx_opcode; } ;
struct mlx5e_tx_wqe {struct mlx5_wqe_ctrl_seg ctrl; } ;
struct mlx5_wq_cyc {int dummy; } ;

/* Variables and functions */
 int MLX5_OPCODE_NOP ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct mlx5_wqe_ctrl_seg*,int /*<<< orphan*/ ,int) ; 
 int mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int) ; 
 struct mlx5e_tx_wqe* mlx5_wq_cyc_get_wqe (struct mlx5_wq_cyc*,int) ; 

__attribute__((used)) static inline struct mlx5e_tx_wqe *
mlx5e_post_nop(struct mlx5_wq_cyc *wq, u32 sqn, u16 *pc)
{
	u16                         pi   = mlx5_wq_cyc_ctr2ix(wq, *pc);
	struct mlx5e_tx_wqe        *wqe  = mlx5_wq_cyc_get_wqe(wq, pi);
	struct mlx5_wqe_ctrl_seg   *cseg = &wqe->ctrl;

	memset(cseg, 0, sizeof(*cseg));

	cseg->opmod_idx_opcode = cpu_to_be32((*pc << 8) | MLX5_OPCODE_NOP);
	cseg->qpn_ds           = cpu_to_be32((sqn << 8) | 0x01);

	(*pc)++;

	return wqe;
}