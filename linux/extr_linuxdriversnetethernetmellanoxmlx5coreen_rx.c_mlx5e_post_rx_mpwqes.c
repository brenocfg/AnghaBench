#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wq_ll {int /*<<< orphan*/  head; } ;
struct TYPE_6__ {int /*<<< orphan*/  umr_in_progress; struct mlx5_wq_ll wq; } ;
struct mlx5e_rq {TYPE_1__* stats; TYPE_2__ mpwqe; TYPE_4__* channel; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int /*<<< orphan*/  cq; } ;
struct TYPE_8__ {TYPE_3__ icosq; } ;
struct TYPE_5__ {int congst_umr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_STATE_ENABLED ; 
 scalar_t__ mlx5_wq_ll_is_full (struct mlx5_wq_ll*) ; 
 int mlx5_wq_ll_missing (struct mlx5_wq_ll*) ; 
 int /*<<< orphan*/  mlx5e_alloc_rx_mpwqe (struct mlx5e_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_poll_ico_cq (int /*<<< orphan*/ *,struct mlx5e_rq*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

bool mlx5e_post_rx_mpwqes(struct mlx5e_rq *rq)
{
	struct mlx5_wq_ll *wq = &rq->mpwqe.wq;

	if (unlikely(!test_bit(MLX5E_RQ_STATE_ENABLED, &rq->state)))
		return false;

	mlx5e_poll_ico_cq(&rq->channel->icosq.cq, rq);

	if (mlx5_wq_ll_is_full(wq))
		return false;

	if (!rq->mpwqe.umr_in_progress)
		mlx5e_alloc_rx_mpwqe(rq, wq->head);
	else
		rq->stats->congst_umr += mlx5_wq_ll_missing(wq) > 2;

	return false;
}