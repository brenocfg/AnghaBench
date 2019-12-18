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
struct mlx5_wq_cyc {int dummy; } ;
struct mlx5e_txqsq {int /*<<< orphan*/  pc; int /*<<< orphan*/  sqn; struct mlx5_wq_cyc wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_post_nop_fence (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_fill_wi (struct mlx5e_txqsq*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tx_post_fence_nop(struct mlx5e_txqsq *sq)
{
	struct mlx5_wq_cyc *wq = &sq->wq;
	u16 pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);

	tx_fill_wi(sq, pi, 1, 0, NULL);

	mlx5e_post_nop_fence(wq, sq->sqn, &sq->pc);
}