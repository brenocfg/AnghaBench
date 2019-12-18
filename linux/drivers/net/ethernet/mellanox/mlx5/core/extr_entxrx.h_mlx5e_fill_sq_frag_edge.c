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
struct TYPE_4__ {struct mlx5e_tx_wqe_info* wqe_info; } ;
struct mlx5e_txqsq {TYPE_1__* stats; int /*<<< orphan*/  pc; int /*<<< orphan*/  sqn; TYPE_2__ db; } ;
struct mlx5e_tx_wqe_info {int num_wqebbs; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nop; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mlx5e_tx_wqe_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5e_post_nop (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
mlx5e_fill_sq_frag_edge(struct mlx5e_txqsq *sq, struct mlx5_wq_cyc *wq,
			u16 pi, u16 nnops)
{
	struct mlx5e_tx_wqe_info *edge_wi, *wi = &sq->db.wqe_info[pi];

	edge_wi = wi + nnops;

	/* fill sq frag edge with nops to avoid wqe wrapping two pages */
	for (; wi < edge_wi; wi++) {
		memset(wi, 0, sizeof(*wi));
		wi->num_wqebbs = 1;
		mlx5e_post_nop(wq, sq->sqn, &sq->pc);
	}
	sq->stats->nop += nnops;
}