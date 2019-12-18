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
struct mlx5_wq_ll {int dummy; } ;
struct TYPE_6__ {scalar_t__ umr_completed; scalar_t__ umr_in_progress; scalar_t__ umr_last_bulk; int /*<<< orphan*/  actual_wq_head; struct mlx5_wq_ll wq; } ;
struct mlx5e_rq {scalar_t__ umem; TYPE_3__ mpwqe; TYPE_2__* stats; int /*<<< orphan*/  state; TYPE_1__* channel; } ;
struct mlx5e_icosq {int /*<<< orphan*/ * doorbell_cseg; int /*<<< orphan*/  uar_map; int /*<<< orphan*/  pc; int /*<<< orphan*/  wq; } ;
struct TYPE_5__ {int /*<<< orphan*/  congst_umr; } ;
struct TYPE_4__ {struct mlx5e_icosq icosq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5E_RQ_STATE_ENABLED ; 
 scalar_t__ UMR_WQE_BULK ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mlx5_wq_ll_get_wqe_next_ix (struct mlx5_wq_ll*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_wq_ll_missing (struct mlx5_wq_ll*) ; 
 int mlx5e_alloc_rx_mpwqe (struct mlx5e_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_notify_hw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_post_rx_mpwqe (struct mlx5e_rq*,scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

bool mlx5e_post_rx_mpwqes(struct mlx5e_rq *rq)
{
	struct mlx5e_icosq *sq = &rq->channel->icosq;
	struct mlx5_wq_ll *wq = &rq->mpwqe.wq;
	u8  umr_completed = rq->mpwqe.umr_completed;
	int alloc_err = 0;
	u8  missing, i;
	u16 head;

	if (unlikely(!test_bit(MLX5E_RQ_STATE_ENABLED, &rq->state)))
		return false;

	if (umr_completed) {
		mlx5e_post_rx_mpwqe(rq, umr_completed);
		rq->mpwqe.umr_in_progress -= umr_completed;
		rq->mpwqe.umr_completed = 0;
	}

	missing = mlx5_wq_ll_missing(wq) - rq->mpwqe.umr_in_progress;

	if (unlikely(rq->mpwqe.umr_in_progress > rq->mpwqe.umr_last_bulk))
		rq->stats->congst_umr++;

#define UMR_WQE_BULK (2)
	if (likely(missing < UMR_WQE_BULK))
		return false;

	head = rq->mpwqe.actual_wq_head;
	i = missing;
	do {
		alloc_err = mlx5e_alloc_rx_mpwqe(rq, head);

		if (unlikely(alloc_err))
			break;
		head = mlx5_wq_ll_get_wqe_next_ix(wq, head);
	} while (--i);

	rq->mpwqe.umr_last_bulk    = missing - i;
	if (sq->doorbell_cseg) {
		mlx5e_notify_hw(&sq->wq, sq->pc, sq->uar_map, sq->doorbell_cseg);
		sq->doorbell_cseg = NULL;
	}

	rq->mpwqe.umr_in_progress += rq->mpwqe.umr_last_bulk;
	rq->mpwqe.actual_wq_head   = head;

	/* If XSK Fill Ring doesn't have enough frames, report the error, so
	 * that one of the actions can be performed:
	 * 1. If need_wakeup is used, signal that the application has to kick
	 * the driver when it refills the Fill Ring.
	 * 2. Otherwise, busy poll by rescheduling the NAPI poll.
	 */
	if (unlikely(alloc_err == -ENOMEM && rq->umem))
		return true;

	return false;
}