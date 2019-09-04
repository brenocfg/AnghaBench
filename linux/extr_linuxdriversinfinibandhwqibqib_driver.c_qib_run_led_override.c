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
struct qib_pportdata {int led_override_timeoff; int /*<<< orphan*/  led_override_timer; scalar_t__* led_override_vals; scalar_t__ led_override; int /*<<< orphan*/  led_override_phase; struct qib_devdata* dd; } ;
struct qib_devdata {int flags; int /*<<< orphan*/  (* f_setextled ) (struct qib_pportdata*,int) ;} ;

/* Variables and functions */
 int QIB_INITTED ; 
 struct qib_pportdata* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_override_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct qib_pportdata* ppd ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int) ; 

__attribute__((used)) static void qib_run_led_override(struct timer_list *t)
{
	struct qib_pportdata *ppd = from_timer(ppd, t,
						    led_override_timer);
	struct qib_devdata *dd = ppd->dd;
	int timeoff;
	int ph_idx;

	if (!(dd->flags & QIB_INITTED))
		return;

	ph_idx = ppd->led_override_phase++ & 1;
	ppd->led_override = ppd->led_override_vals[ph_idx];
	timeoff = ppd->led_override_timeoff;

	dd->f_setextled(ppd, 1);
	/*
	 * don't re-fire the timer if user asked for it to be off; we let
	 * it fire one more time after they turn it off to simplify
	 */
	if (ppd->led_override_vals[0] || ppd->led_override_vals[1])
		mod_timer(&ppd->led_override_timer, jiffies + timeoff);
}