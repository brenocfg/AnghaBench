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
struct TYPE_4__ {int /*<<< orphan*/  next_wqe_index; } ;
struct mlx5e_rx_wqe_ll {TYPE_2__ next; } ;
struct mlx5_wq_ll {int /*<<< orphan*/  head; } ;
struct TYPE_3__ {int umr_in_progress; struct mlx5_wq_ll wq; } ;
struct mlx5e_rq {TYPE_1__ mpwqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 struct mlx5e_rx_wqe_ll* mlx5_wq_ll_get_wqe (struct mlx5_wq_ll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_ll_push (struct mlx5_wq_ll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_ll_update_db_record (struct mlx5_wq_ll*) ; 

__attribute__((used)) static void mlx5e_post_rx_mpwqe(struct mlx5e_rq *rq)
{
	struct mlx5_wq_ll *wq = &rq->mpwqe.wq;
	struct mlx5e_rx_wqe_ll *wqe = mlx5_wq_ll_get_wqe(wq, wq->head);

	rq->mpwqe.umr_in_progress = false;

	mlx5_wq_ll_push(wq, be16_to_cpu(wqe->next.next_wqe_index));

	/* ensure wqes are visible to device before updating doorbell record */
	dma_wmb();

	mlx5_wq_ll_update_db_record(wq);
}