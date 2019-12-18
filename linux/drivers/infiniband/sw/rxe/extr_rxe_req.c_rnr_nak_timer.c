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
struct TYPE_2__ {int /*<<< orphan*/  task; } ;
struct rxe_qp {TYPE_1__ req; } ;

/* Variables and functions */
 struct rxe_qp* from_timer (int /*<<< orphan*/ ,struct timer_list*,void (*) (struct timer_list*)) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 struct rxe_qp* qp ; 
 int /*<<< orphan*/  qp_num (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 

void rnr_nak_timer(struct timer_list *t)
{
	struct rxe_qp *qp = from_timer(qp, t, rnr_nak_timer);

	pr_debug("qp#%d rnr nak timer fired\n", qp_num(qp));
	rxe_run_task(&qp->req.task, 1);
}