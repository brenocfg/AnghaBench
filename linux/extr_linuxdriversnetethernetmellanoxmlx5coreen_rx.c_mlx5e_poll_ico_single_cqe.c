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
struct mlx5e_sq_wqe_info {int opcode; } ;
struct mlx5e_rq {int dummy; } ;
struct TYPE_3__ {struct mlx5e_sq_wqe_info* ico_wqe; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct mlx5e_icosq {TYPE_1__ db; struct mlx5_wq_cyc wq; } ;
struct mlx5e_cq {TYPE_2__* channel; int /*<<< orphan*/  wq; } ;
struct mlx5_cqe64 {int op_own; int /*<<< orphan*/  wqe_counter; } ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int MLX5_CQE_REQ ; 
 int MLX5_OPCODE_NOP ; 
 int MLX5_OPCODE_UMR ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mlx5_cqwq_pop (int /*<<< orphan*/ *) ; 
 size_t mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_post_rx_mpwqe (struct mlx5e_rq*) ; 
 int /*<<< orphan*/  netdev_WARN_ONCE (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void mlx5e_poll_ico_single_cqe(struct mlx5e_cq *cq,
					     struct mlx5e_icosq *sq,
					     struct mlx5e_rq *rq,
					     struct mlx5_cqe64 *cqe)
{
	struct mlx5_wq_cyc *wq = &sq->wq;
	u16 ci = mlx5_wq_cyc_ctr2ix(wq, be16_to_cpu(cqe->wqe_counter));
	struct mlx5e_sq_wqe_info *icowi = &sq->db.ico_wqe[ci];

	mlx5_cqwq_pop(&cq->wq);

	if (unlikely((cqe->op_own >> 4) != MLX5_CQE_REQ)) {
		netdev_WARN_ONCE(cq->channel->netdev,
				 "Bad OP in ICOSQ CQE: 0x%x\n", cqe->op_own);
		return;
	}

	if (likely(icowi->opcode == MLX5_OPCODE_UMR)) {
		mlx5e_post_rx_mpwqe(rq);
		return;
	}

	if (unlikely(icowi->opcode != MLX5_OPCODE_NOP))
		netdev_WARN_ONCE(cq->channel->netdev,
				 "Bad OPCODE in ICOSQ WQE info: 0x%x\n", icowi->opcode);
}