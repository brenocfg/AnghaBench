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
struct timer_list {int dummy; } ;
struct qib_pportdata {int lflags; } ;
struct qib_devdata {int flags; struct qib_pportdata* pport; } ;
struct qib_chip_specific {int relock_interval; int /*<<< orphan*/  relock_timer; struct qib_devdata* dd; } ;

/* Variables and functions */
 int HZ ; 
 int QIBL_IB_AUTONEG_INPROG ; 
 int QIBL_IB_LINK_DISABLED ; 
 int QIBL_LINKACTIVE ; 
 int QIBL_LINKARMED ; 
 int QIBL_LINKINIT ; 
 int QIB_INITTED ; 
 struct qib_chip_specific* cs ; 
 struct qib_chip_specific* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ qib_relock_by_timer ; 
 int /*<<< orphan*/  relock_timer ; 
 int /*<<< orphan*/  toggle_7220_rclkrls (struct qib_devdata*) ; 

__attribute__((used)) static void qib_run_relock(struct timer_list *t)
{
	struct qib_chip_specific *cs = from_timer(cs, t, relock_timer);
	struct qib_devdata *dd = cs->dd;
	struct qib_pportdata *ppd = dd->pport;
	int timeoff;

	/*
	 * Check link-training state for "stuck" state, when down.
	 * if found, try relock and schedule another try at
	 * exponentially growing delay, maxed at one second.
	 * if not stuck, our work is done.
	 */
	if ((dd->flags & QIB_INITTED) && !(ppd->lflags &
	    (QIBL_IB_AUTONEG_INPROG | QIBL_LINKINIT | QIBL_LINKARMED |
	     QIBL_LINKACTIVE))) {
		if (qib_relock_by_timer) {
			if (!(ppd->lflags & QIBL_IB_LINK_DISABLED))
				toggle_7220_rclkrls(dd);
		}
		/* re-set timer for next check */
		timeoff = cs->relock_interval << 1;
		if (timeoff > HZ)
			timeoff = HZ;
		cs->relock_interval = timeoff;
	} else
		timeoff = HZ;
	mod_timer(&cs->relock_timer, jiffies + timeoff);
}