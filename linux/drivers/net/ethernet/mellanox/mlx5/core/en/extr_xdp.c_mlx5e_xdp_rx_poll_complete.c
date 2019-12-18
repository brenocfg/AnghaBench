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
struct TYPE_2__ {scalar_t__ wqe; } ;
struct mlx5e_xdpsq {TYPE_1__ mpwqe; } ;
struct mlx5e_rq {int /*<<< orphan*/  flags; struct mlx5e_xdpsq* xdpsq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_FLAG_XDP_REDIRECT ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_xdp_mpwqe_complete (struct mlx5e_xdpsq*) ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_doorbell (struct mlx5e_xdpsq*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_do_flush_map () ; 

void mlx5e_xdp_rx_poll_complete(struct mlx5e_rq *rq)
{
	struct mlx5e_xdpsq *xdpsq = rq->xdpsq;

	if (xdpsq->mpwqe.wqe)
		mlx5e_xdp_mpwqe_complete(xdpsq);

	mlx5e_xmit_xdp_doorbell(xdpsq);

	if (test_bit(MLX5E_RQ_FLAG_XDP_REDIRECT, rq->flags)) {
		xdp_do_flush_map();
		__clear_bit(MLX5E_RQ_FLAG_XDP_REDIRECT, rq->flags);
	}
}