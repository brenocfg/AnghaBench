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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5e_txqsq {int /*<<< orphan*/  pc; int /*<<< orphan*/  sqn; } ;
struct mlx5e_tx_wqe {int dummy; } ;
struct mlx5e_ktls_offload_context_tx {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5E_KTLS_PROGRESS_WQEBBS ; 
 int /*<<< orphan*/  MLX5E_KTLS_PROGRESS_WQE_SZ ; 
 int /*<<< orphan*/  build_progress_params (struct mlx5e_tx_wqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5e_ktls_offload_context_tx*,int) ; 
 struct mlx5e_tx_wqe* mlx5e_sq_fetch_wqe (struct mlx5e_txqsq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_fill_wi (struct mlx5e_txqsq*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
post_progress_params(struct mlx5e_txqsq *sq,
		     struct mlx5e_ktls_offload_context_tx *priv_tx,
		     bool fence)
{
	struct mlx5e_tx_wqe *wqe;
	u16 pi;

	wqe = mlx5e_sq_fetch_wqe(sq, MLX5E_KTLS_PROGRESS_WQE_SZ, &pi);
	build_progress_params(wqe, sq->pc, sq->sqn, priv_tx, fence);
	tx_fill_wi(sq, pi, MLX5E_KTLS_PROGRESS_WQEBBS, 0, NULL);
	sq->pc += MLX5E_KTLS_PROGRESS_WQEBBS;
}