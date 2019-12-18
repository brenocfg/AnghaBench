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
typedef  scalar_t__ u16 ;
struct mlx5_wq_cyc {int dummy; } ;
struct mlx5e_txqsq {int /*<<< orphan*/  pc; struct mlx5_wq_cyc wq; } ;
struct mlx5e_ktls_offload_context_tx {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5E_KTLS_PROGRESS_WQEBBS ; 
 scalar_t__ MLX5E_KTLS_STATIC_WQEBBS ; 
 scalar_t__ mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_wq_cyc_get_contig_wqebbs (struct mlx5_wq_cyc*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5e_fill_sq_frag_edge (struct mlx5e_txqsq*,struct mlx5_wq_cyc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  post_progress_params (struct mlx5e_txqsq*,struct mlx5e_ktls_offload_context_tx*,int) ; 
 int /*<<< orphan*/  post_static_params (struct mlx5e_txqsq*,struct mlx5e_ktls_offload_context_tx*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
mlx5e_ktls_tx_post_param_wqes(struct mlx5e_txqsq *sq,
			      struct mlx5e_ktls_offload_context_tx *priv_tx,
			      bool skip_static_post, bool fence_first_post)
{
	bool progress_fence = skip_static_post || !fence_first_post;
	struct mlx5_wq_cyc *wq = &sq->wq;
	u16 contig_wqebbs_room, pi;

	pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	contig_wqebbs_room = mlx5_wq_cyc_get_contig_wqebbs(wq, pi);
	if (unlikely(contig_wqebbs_room <
		     MLX5E_KTLS_STATIC_WQEBBS + MLX5E_KTLS_PROGRESS_WQEBBS))
		mlx5e_fill_sq_frag_edge(sq, wq, pi, contig_wqebbs_room);

	if (!skip_static_post)
		post_static_params(sq, priv_tx, fence_first_post);

	post_progress_params(sq, priv_tx, progress_fence);
}