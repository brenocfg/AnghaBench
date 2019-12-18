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
struct mlx5e_rq {int /*<<< orphan*/  recover_work; TYPE_2__* channel; int /*<<< orphan*/  state; } ;
struct mlx5_err_cqe {int /*<<< orphan*/  syndrome; } ;
struct mlx5_cqe64 {int dummy; } ;
struct TYPE_4__ {TYPE_1__* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_STATE_RECOVERING ; 
 scalar_t__ cqe_syndrome_needs_recover (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void trigger_report(struct mlx5e_rq *rq, struct mlx5_cqe64 *cqe)
{
	struct mlx5_err_cqe *err_cqe = (struct mlx5_err_cqe *)cqe;

	if (cqe_syndrome_needs_recover(err_cqe->syndrome) &&
	    !test_and_set_bit(MLX5E_RQ_STATE_RECOVERING, &rq->state))
		queue_work(rq->channel->priv->wq, &rq->recover_work);
}