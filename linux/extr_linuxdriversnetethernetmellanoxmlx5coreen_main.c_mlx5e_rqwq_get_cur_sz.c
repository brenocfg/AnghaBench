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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  cur_sz; } ;
struct TYPE_8__ {TYPE_3__ wq; } ;
struct TYPE_5__ {int /*<<< orphan*/  cur_sz; } ;
struct TYPE_6__ {TYPE_1__ wq; } ;
struct mlx5e_rq {int wq_type; TYPE_4__ wqe; TYPE_2__ mpwqe; } ;

/* Variables and functions */
#define  MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ 128 

__attribute__((used)) static u32 mlx5e_rqwq_get_cur_sz(struct mlx5e_rq *rq)
{
	switch (rq->wq_type) {
	case MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		return rq->mpwqe.wq.cur_sz;
	default:
		return rq->wqe.wq.cur_sz;
	}
}