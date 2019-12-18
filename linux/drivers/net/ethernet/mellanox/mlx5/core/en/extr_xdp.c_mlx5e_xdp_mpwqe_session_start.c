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
typedef  scalar_t__ u16 ;
struct mlx5e_xdpsq_stats {int /*<<< orphan*/  mpwqe; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct mlx5e_xdp_mpwqe {scalar_t__ pkt_count; int /*<<< orphan*/  ds_count; TYPE_1__* wqe; } ;
struct mlx5e_xdpsq {int /*<<< orphan*/  pc; struct mlx5_wq_cyc wq; struct mlx5e_xdpsq_stats* stats; struct mlx5e_xdp_mpwqe mpwqe; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_XDP_TX_EMPTY_DS_COUNT ; 
 scalar_t__ MLX5_SEND_WQE_MAX_WQEBBS ; 
 scalar_t__ mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_wq_cyc_get_contig_wqebbs (struct mlx5_wq_cyc*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5e_fill_xdpsq_frag_edge (struct mlx5e_xdpsq*,struct mlx5_wq_cyc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlx5e_xdp_update_inline_state (struct mlx5e_xdpsq*) ; 
 TYPE_1__* mlx5e_xdpsq_fetch_wqe (struct mlx5e_xdpsq*,scalar_t__*) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mlx5e_xdp_mpwqe_session_start(struct mlx5e_xdpsq *sq)
{
	struct mlx5e_xdp_mpwqe *session = &sq->mpwqe;
	struct mlx5e_xdpsq_stats *stats = sq->stats;
	struct mlx5_wq_cyc *wq = &sq->wq;
	u16 pi, contig_wqebbs;

	pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	contig_wqebbs = mlx5_wq_cyc_get_contig_wqebbs(wq, pi);

	if (unlikely(contig_wqebbs < MLX5_SEND_WQE_MAX_WQEBBS))
		mlx5e_fill_xdpsq_frag_edge(sq, wq, pi, contig_wqebbs);

	session->wqe = mlx5e_xdpsq_fetch_wqe(sq, &pi);

	prefetchw(session->wqe->data);
	session->ds_count  = MLX5E_XDP_TX_EMPTY_DS_COUNT;
	session->pkt_count = 0;

	mlx5e_xdp_update_inline_state(sq);

	stats->mpwqe++;
}