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
typedef  int u16 ;
struct TYPE_4__ {int wqe_cnt; int last_poll; TYPE_1__* w_list; } ;
struct mlx5_ib_qp {TYPE_2__ sq; } ;
struct mlx5_cqe64 {int dummy; } ;
struct TYPE_3__ {int next; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_atomic (struct mlx5_ib_qp*,struct mlx5_cqe64*,int) ; 

__attribute__((used)) static void handle_atomics(struct mlx5_ib_qp *qp, struct mlx5_cqe64 *cqe64,
			   u16 tail, u16 head)
{
	u16 idx;

	do {
		idx = tail & (qp->sq.wqe_cnt - 1);
		handle_atomic(qp, cqe64, idx);
		if (idx == head)
			break;

		tail = qp->sq.w_list[idx].next;
	} while (1);
	tail = qp->sq.w_list[idx].next;
	qp->sq.last_poll = tail;
}