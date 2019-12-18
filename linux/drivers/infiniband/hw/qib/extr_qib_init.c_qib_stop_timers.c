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
struct TYPE_2__ {scalar_t__ function; } ;
struct qib_pportdata {TYPE_1__ symerr_clear_timer; int /*<<< orphan*/  led_override_timer_active; TYPE_1__ led_override_timer; TYPE_1__ hol_timer; } ;
struct qib_devdata {int num_pports; struct qib_pportdata* pport; TYPE_1__ intrchk_timer; TYPE_1__ stats_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 

__attribute__((used)) static void qib_stop_timers(struct qib_devdata *dd)
{
	struct qib_pportdata *ppd;
	int pidx;

	if (dd->stats_timer.function)
		del_timer_sync(&dd->stats_timer);
	if (dd->intrchk_timer.function)
		del_timer_sync(&dd->intrchk_timer);
	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;
		if (ppd->hol_timer.function)
			del_timer_sync(&ppd->hol_timer);
		if (ppd->led_override_timer.function) {
			del_timer_sync(&ppd->led_override_timer);
			atomic_set(&ppd->led_override_timer_active, 0);
		}
		if (ppd->symerr_clear_timer.function)
			del_timer_sync(&ppd->symerr_clear_timer);
	}
}