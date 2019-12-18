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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  wq; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq; } ;
struct mlx5e_rq {int wq_type; TYPE_2__ wqe; TYPE_1__ mpwqe; } ;

/* Variables and functions */
#define  MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ 128 
 int /*<<< orphan*/  mlx5_wq_cyc_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_ll_get_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 mlx5e_rqwq_get_size(struct mlx5e_rq *rq)
{
	switch (rq->wq_type) {
	case MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		return mlx5_wq_ll_get_size(&rq->mpwqe.wq);
	default:
		return mlx5_wq_cyc_get_size(&rq->wqe.wq);
	}
}