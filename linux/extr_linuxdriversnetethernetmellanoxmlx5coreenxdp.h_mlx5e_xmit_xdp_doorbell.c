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
struct mlx5e_xdpsq {int /*<<< orphan*/  uar_map; scalar_t__ pc; struct mlx5_wq_cyc wq; } ;
struct mlx5e_tx_wqe {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,scalar_t__) ; 
 struct mlx5e_tx_wqe* mlx5_wq_cyc_get_wqe (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_notify_hw (struct mlx5_wq_cyc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mlx5e_xmit_xdp_doorbell(struct mlx5e_xdpsq *sq)
{
	struct mlx5_wq_cyc *wq = &sq->wq;
	struct mlx5e_tx_wqe *wqe;
	u16 pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc - 1); /* last pi */

	wqe  = mlx5_wq_cyc_get_wqe(wq, pi);

	mlx5e_notify_hw(wq, sq->pc, sq->uar_map, &wqe->ctrl);
}