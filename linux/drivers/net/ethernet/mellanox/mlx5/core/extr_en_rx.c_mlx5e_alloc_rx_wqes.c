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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct mlx5e_rx_wqe_cyc {int dummy; } ;
struct TYPE_4__ {int log_num_frags; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct TYPE_3__ {TYPE_2__ info; struct mlx5_wq_cyc wq; } ;
struct mlx5e_rq {TYPE_1__ wqe; scalar_t__ umem; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlx5e_rx_wqe_cyc* mlx5_wq_cyc_get_wqe (struct mlx5_wq_cyc*,scalar_t__) ; 
 int mlx5e_alloc_rx_wqe (struct mlx5e_rq*,struct mlx5e_rx_wqe_cyc*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5e_dealloc_rx_wqe (struct mlx5e_rq*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5e_xsk_pages_enough_umem (struct mlx5e_rq*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5e_alloc_rx_wqes(struct mlx5e_rq *rq, u16 ix, u8 wqe_bulk)
{
	struct mlx5_wq_cyc *wq = &rq->wqe.wq;
	int err;
	int i;

	if (rq->umem) {
		int pages_desired = wqe_bulk << rq->wqe.info.log_num_frags;

		if (unlikely(!mlx5e_xsk_pages_enough_umem(rq, pages_desired)))
			return -ENOMEM;
	}

	for (i = 0; i < wqe_bulk; i++) {
		struct mlx5e_rx_wqe_cyc *wqe = mlx5_wq_cyc_get_wqe(wq, ix + i);

		err = mlx5e_alloc_rx_wqe(rq, wqe, ix + i);
		if (unlikely(err))
			goto free_wqes;
	}

	return 0;

free_wqes:
	while (--i >= 0)
		mlx5e_dealloc_rx_wqe(rq, ix + i);

	return err;
}