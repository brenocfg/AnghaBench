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
struct mlx5e_xdpsq {int /*<<< orphan*/  pc; struct mlx5_wq_cyc wq; } ;
struct mlx5e_tx_wqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mlx5e_tx_wqe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 struct mlx5e_tx_wqe* mlx5_wq_cyc_get_wqe (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mlx5e_tx_wqe *
mlx5e_xdpsq_fetch_wqe(struct mlx5e_xdpsq *sq, u16 *pi)
{
	struct mlx5_wq_cyc *wq = &sq->wq;
	struct mlx5e_tx_wqe *wqe;

	*pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	wqe = mlx5_wq_cyc_get_wqe(wq, *pi);
	memset(wqe, 0, sizeof(*wqe));

	return wqe;
}