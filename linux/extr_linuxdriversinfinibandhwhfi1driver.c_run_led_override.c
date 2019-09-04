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
struct hfi1_pportdata {int led_override_phase; unsigned long* led_override_vals; int /*<<< orphan*/  led_override_timer; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int flags; } ;

/* Variables and functions */
 int HFI1_INITTED ; 
 struct hfi1_pportdata* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_override_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct hfi1_pportdata* ppd ; 
 int /*<<< orphan*/  setextled (struct hfi1_devdata*,int) ; 

__attribute__((used)) static void run_led_override(struct timer_list *t)
{
	struct hfi1_pportdata *ppd = from_timer(ppd, t, led_override_timer);
	struct hfi1_devdata *dd = ppd->dd;
	unsigned long timeout;
	int phase_idx;

	if (!(dd->flags & HFI1_INITTED))
		return;

	phase_idx = ppd->led_override_phase & 1;

	setextled(dd, phase_idx);

	timeout = ppd->led_override_vals[phase_idx];

	/* Set up for next phase */
	ppd->led_override_phase = !ppd->led_override_phase;

	mod_timer(&ppd->led_override_timer, jiffies + timeout);
}