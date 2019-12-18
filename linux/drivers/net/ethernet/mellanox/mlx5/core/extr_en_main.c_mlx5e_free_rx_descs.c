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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  next_wqe_index; } ;
struct mlx5e_rx_wqe_ll {TYPE_2__ next; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct TYPE_6__ {struct mlx5_wq_cyc wq; } ;
struct mlx5_wq_ll {int /*<<< orphan*/ * tail_next; int /*<<< orphan*/  head; } ;
struct TYPE_4__ {int umr_in_progress; struct mlx5_wq_ll wq; } ;
struct mlx5e_rq {scalar_t__ wq_type; int /*<<< orphan*/  (* dealloc_wqe ) (struct mlx5e_rq*,int /*<<< orphan*/ ) ;TYPE_3__ wqe; TYPE_1__ mpwqe; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_get_tail (struct mlx5_wq_cyc*) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_is_empty (struct mlx5_wq_cyc*) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_pop (struct mlx5_wq_cyc*) ; 
 struct mlx5e_rx_wqe_ll* mlx5_wq_ll_get_wqe (struct mlx5_wq_ll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_ll_get_wqe_next_ix (struct mlx5_wq_ll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_ll_is_empty (struct mlx5_wq_ll*) ; 
 int /*<<< orphan*/  mlx5_wq_ll_pop (struct mlx5_wq_ll*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mlx5e_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mlx5e_rq*,int /*<<< orphan*/ ) ; 

void mlx5e_free_rx_descs(struct mlx5e_rq *rq)
{
	__be16 wqe_ix_be;
	u16 wqe_ix;

	if (rq->wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ) {
		struct mlx5_wq_ll *wq = &rq->mpwqe.wq;
		u16 head = wq->head;
		int i;

		/* Outstanding UMR WQEs (in progress) start at wq->head */
		for (i = 0; i < rq->mpwqe.umr_in_progress; i++) {
			rq->dealloc_wqe(rq, head);
			head = mlx5_wq_ll_get_wqe_next_ix(wq, head);
		}

		while (!mlx5_wq_ll_is_empty(wq)) {
			struct mlx5e_rx_wqe_ll *wqe;

			wqe_ix_be = *wq->tail_next;
			wqe_ix    = be16_to_cpu(wqe_ix_be);
			wqe       = mlx5_wq_ll_get_wqe(wq, wqe_ix);
			rq->dealloc_wqe(rq, wqe_ix);
			mlx5_wq_ll_pop(wq, wqe_ix_be,
				       &wqe->next.next_wqe_index);
		}
	} else {
		struct mlx5_wq_cyc *wq = &rq->wqe.wq;

		while (!mlx5_wq_cyc_is_empty(wq)) {
			wqe_ix = mlx5_wq_cyc_get_tail(wq);
			rq->dealloc_wqe(rq, wqe_ix);
			mlx5_wq_cyc_pop(wq);
		}
	}

}