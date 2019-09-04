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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {scalar_t__ wqe_bulk; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct TYPE_5__ {TYPE_3__ info; struct mlx5_wq_cyc wq; } ;
struct mlx5e_rq {TYPE_1__* stats; TYPE_2__ wqe; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  buff_alloc_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_STATE_ENABLED ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  mlx5_wq_cyc_get_head (struct mlx5_wq_cyc*) ; 
 scalar_t__ mlx5_wq_cyc_missing (struct mlx5_wq_cyc*) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_push_n (struct mlx5_wq_cyc*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_update_db_record (struct mlx5_wq_cyc*) ; 
 int mlx5e_alloc_rx_wqes (struct mlx5e_rq*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

bool mlx5e_post_rx_wqes(struct mlx5e_rq *rq)
{
	struct mlx5_wq_cyc *wq = &rq->wqe.wq;
	u8 wqe_bulk;
	int err;

	if (unlikely(!test_bit(MLX5E_RQ_STATE_ENABLED, &rq->state)))
		return false;

	wqe_bulk = rq->wqe.info.wqe_bulk;

	if (mlx5_wq_cyc_missing(wq) < wqe_bulk)
		return false;

	do {
		u16 head = mlx5_wq_cyc_get_head(wq);

		err = mlx5e_alloc_rx_wqes(rq, head, wqe_bulk);
		if (unlikely(err)) {
			rq->stats->buff_alloc_err++;
			break;
		}

		mlx5_wq_cyc_push_n(wq, wqe_bulk);
	} while (mlx5_wq_cyc_missing(wq) >= wqe_bulk);

	/* ensure wqes are visible to device before updating doorbell record */
	dma_wmb();

	mlx5_wq_cyc_update_db_record(wq);

	return !!err;
}