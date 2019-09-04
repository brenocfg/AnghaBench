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
struct rvt_qp {int /*<<< orphan*/  s_rnr_timer; int /*<<< orphan*/  s_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

void rvt_del_timers_sync(struct rvt_qp *qp)
{
	del_timer_sync(&qp->s_timer);
	hrtimer_cancel(&qp->s_rnr_timer);
}