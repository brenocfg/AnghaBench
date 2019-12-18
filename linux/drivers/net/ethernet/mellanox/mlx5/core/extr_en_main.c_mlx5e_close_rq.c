#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct mlx5e_rq {int /*<<< orphan*/  recover_work; TYPE_3__* channel; TYPE_1__ dim; } ;
struct TYPE_5__ {int /*<<< orphan*/  recover_work; } ;
struct TYPE_6__ {TYPE_2__ icosq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_rq (struct mlx5e_rq*) ; 
 int /*<<< orphan*/  mlx5e_free_rq (struct mlx5e_rq*) ; 
 int /*<<< orphan*/  mlx5e_free_rx_descs (struct mlx5e_rq*) ; 

void mlx5e_close_rq(struct mlx5e_rq *rq)
{
	cancel_work_sync(&rq->dim.work);
	cancel_work_sync(&rq->channel->icosq.recover_work);
	cancel_work_sync(&rq->recover_work);
	mlx5e_destroy_rq(rq);
	mlx5e_free_rx_descs(rq);
	mlx5e_free_rq(rq);
}