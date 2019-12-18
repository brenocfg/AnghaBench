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
struct mlx5e_tx_wqe {int /*<<< orphan*/  ctrl; } ;
struct TYPE_4__ {TYPE_1__* ico_wqe; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct mlx5e_icosq {int /*<<< orphan*/  uar_map; int /*<<< orphan*/  pc; int /*<<< orphan*/  sqn; TYPE_2__ db; struct mlx5_wq_cyc wq; } ;
struct TYPE_3__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_OPCODE_NOP ; 
 size_t mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_notify_hw (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5e_tx_wqe* mlx5e_post_nop (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5e_trigger_irq(struct mlx5e_icosq *sq)
{
	struct mlx5_wq_cyc *wq = &sq->wq;
	struct mlx5e_tx_wqe *nopwqe;
	u16 pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);

	sq->db.ico_wqe[pi].opcode = MLX5_OPCODE_NOP;
	nopwqe = mlx5e_post_nop(wq, sq->sqn, &sq->pc);
	mlx5e_notify_hw(wq, sq->pc, sq->uar_map, &nopwqe->ctrl);
}