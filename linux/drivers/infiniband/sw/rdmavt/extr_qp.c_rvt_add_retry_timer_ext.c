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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct rvt_qp {int timeout_jiffies; TYPE_1__ s_timer; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_lock; struct ib_qp ibqp; } ;
struct rvt_dev_info {scalar_t__ busy_jiffies; } ;

/* Variables and functions */
 int /*<<< orphan*/  RVT_S_TIMER ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void rvt_add_retry_timer_ext(struct rvt_qp *qp, u8 shift)
{
	struct ib_qp *ibqp = &qp->ibqp;
	struct rvt_dev_info *rdi = ib_to_rvt(ibqp->device);

	lockdep_assert_held(&qp->s_lock);
	qp->s_flags |= RVT_S_TIMER;
       /* 4.096 usec. * (1 << qp->timeout) */
	qp->s_timer.expires = jiffies + rdi->busy_jiffies +
			      (qp->timeout_jiffies << shift);
	add_timer(&qp->s_timer);
}