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
typedef  int u32 ;
struct rvt_qp {int /*<<< orphan*/  s_rnr_timer; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int /*<<< orphan*/  RVT_S_WAIT_RNR ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 int rvt_aeth_to_usec (int) ; 
 int /*<<< orphan*/  trace_rvt_rnrnak_add (struct rvt_qp*,int) ; 

void rvt_add_rnr_timer(struct rvt_qp *qp, u32 aeth)
{
	u32 to;

	lockdep_assert_held(&qp->s_lock);
	qp->s_flags |= RVT_S_WAIT_RNR;
	to = rvt_aeth_to_usec(aeth);
	trace_rvt_rnrnak_add(qp, to);
	hrtimer_start(&qp->s_rnr_timer,
		      ns_to_ktime(1000 * to), HRTIMER_MODE_REL_PINNED);
}