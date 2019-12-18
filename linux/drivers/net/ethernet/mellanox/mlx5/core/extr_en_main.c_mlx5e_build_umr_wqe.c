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
typedef  int u8 ;
struct mlx5_wqe_umr_ctrl_seg {int flags; int /*<<< orphan*/  mkey_mask; int /*<<< orphan*/  xlt_octowords; } ;
struct mlx5_wqe_ctrl_seg {int /*<<< orphan*/  imm; int /*<<< orphan*/  fm_ce_se; int /*<<< orphan*/  qpn_ds; } ;
struct mlx5e_umr_wqe {struct mlx5_wqe_umr_ctrl_seg uctrl; struct mlx5_wqe_ctrl_seg ctrl; } ;
struct mlx5e_rq {int /*<<< orphan*/  mkey_be; } ;
struct mlx5e_icosq {int sqn; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_UMR_WQE_INLINE_SZ ; 
 int /*<<< orphan*/  MLX5_MKEY_MASK_FREE ; 
 int /*<<< orphan*/  MLX5_MPWRQ_PAGES_PER_WQE ; 
 int /*<<< orphan*/  MLX5_MTT_OCTW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SEND_WQE_DS ; 
 int MLX5_UMR_INLINE ; 
 int MLX5_UMR_TRANSLATION_OFFSET_EN ; 
 int /*<<< orphan*/  MLX5_WQE_CTRL_CQ_UPDATE ; 
 int MLX5_WQE_CTRL_QPN_SHIFT ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlx5e_build_umr_wqe(struct mlx5e_rq *rq,
				       struct mlx5e_icosq *sq,
				       struct mlx5e_umr_wqe *wqe)
{
	struct mlx5_wqe_ctrl_seg      *cseg = &wqe->ctrl;
	struct mlx5_wqe_umr_ctrl_seg *ucseg = &wqe->uctrl;
	u8 ds_cnt = DIV_ROUND_UP(MLX5E_UMR_WQE_INLINE_SZ, MLX5_SEND_WQE_DS);

	cseg->qpn_ds    = cpu_to_be32((sq->sqn << MLX5_WQE_CTRL_QPN_SHIFT) |
				      ds_cnt);
	cseg->fm_ce_se  = MLX5_WQE_CTRL_CQ_UPDATE;
	cseg->imm       = rq->mkey_be;

	ucseg->flags = MLX5_UMR_TRANSLATION_OFFSET_EN | MLX5_UMR_INLINE;
	ucseg->xlt_octowords =
		cpu_to_be16(MLX5_MTT_OCTW(MLX5_MPWRQ_PAGES_PER_WQE));
	ucseg->mkey_mask     = cpu_to_be64(MLX5_MKEY_MASK_FREE);
}