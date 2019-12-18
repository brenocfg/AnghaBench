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
typedef  size_t u16 ;
struct mlx5e_sq_wqe_info {int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {struct mlx5e_sq_wqe_info* ico_wqe; } ;
struct mlx5e_icosq {int /*<<< orphan*/  pc; int /*<<< orphan*/  sqn; TYPE_1__ db; } ;
struct mlx5_wq_cyc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_OPCODE_NOP ; 
 int /*<<< orphan*/  mlx5e_post_nop (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mlx5e_fill_icosq_frag_edge(struct mlx5e_icosq *sq,
					      struct mlx5_wq_cyc *wq,
					      u16 pi, u16 nnops)
{
	struct mlx5e_sq_wqe_info *edge_wi, *wi = &sq->db.ico_wqe[pi];

	edge_wi = wi + nnops;

	/* fill sq frag edge with nops to avoid wqe wrapping two pages */
	for (; wi < edge_wi; wi++) {
		wi->opcode = MLX5_OPCODE_NOP;
		mlx5e_post_nop(wq, sq->sqn, &sq->pc);
	}
}