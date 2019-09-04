#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rvt_qp {int s_flags; int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 int RVT_S_WAIT_RNR ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rvt_rnrnak_stop (struct rvt_qp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvt_stop_rnr_timer(struct rvt_qp *qp)
{
	lockdep_assert_held(&qp->s_lock);
	/* Remove QP from rnr timer */
	if (qp->s_flags & RVT_S_WAIT_RNR) {
		qp->s_flags &= ~RVT_S_WAIT_RNR;
		trace_rvt_rnrnak_stop(qp, 0);
	}
}