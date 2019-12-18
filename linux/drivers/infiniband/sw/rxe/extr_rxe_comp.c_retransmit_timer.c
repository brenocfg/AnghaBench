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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int timeout; int /*<<< orphan*/  task; } ;
struct rxe_qp {TYPE_1__ comp; scalar_t__ valid; } ;

/* Variables and functions */
 struct rxe_qp* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct rxe_qp* qp ; 
 int /*<<< orphan*/  retrans_timer ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 

void retransmit_timer(struct timer_list *t)
{
	struct rxe_qp *qp = from_timer(qp, t, retrans_timer);

	if (qp->valid) {
		qp->comp.timeout = 1;
		rxe_run_task(&qp->comp.task, 1);
	}
}