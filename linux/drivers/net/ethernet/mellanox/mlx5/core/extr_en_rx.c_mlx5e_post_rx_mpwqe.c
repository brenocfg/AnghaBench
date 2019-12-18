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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_wq_ll {int /*<<< orphan*/  head; } ;
struct TYPE_2__ {struct mlx5_wq_ll wq; } ;
struct mlx5e_rq {TYPE_1__ mpwqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  mlx5_wq_ll_get_wqe_next_ix (struct mlx5_wq_ll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_ll_push (struct mlx5_wq_ll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_ll_update_db_record (struct mlx5_wq_ll*) ; 

__attribute__((used)) static void mlx5e_post_rx_mpwqe(struct mlx5e_rq *rq, u8 n)
{
	struct mlx5_wq_ll *wq = &rq->mpwqe.wq;

	do {
		u16 next_wqe_index = mlx5_wq_ll_get_wqe_next_ix(wq, wq->head);

		mlx5_wq_ll_push(wq, next_wqe_index);
	} while (--n);

	/* ensure wqes are visible to device before updating doorbell record */
	dma_wmb();

	mlx5_wq_ll_update_db_record(wq);
}