#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ expires; } ;
struct hfi1_pportdata {int led_override_phase; int /*<<< orphan*/  led_override_timer_active; TYPE_2__ led_override_timer; void** led_override_vals; TYPE_1__* dd; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int HFI1_INITTED ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ jiffies ; 
 void* msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  run_led_override ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  timer_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hfi1_start_led_override(struct hfi1_pportdata *ppd, unsigned int timeon,
			     unsigned int timeoff)
{
	if (!(ppd->dd->flags & HFI1_INITTED))
		return;

	/* Convert to jiffies for direct use in timer */
	ppd->led_override_vals[0] = msecs_to_jiffies(timeoff);
	ppd->led_override_vals[1] = msecs_to_jiffies(timeon);

	/* Arbitrarily start from LED on phase */
	ppd->led_override_phase = 1;

	/*
	 * If the timer has not already been started, do so. Use a "quick"
	 * timeout so the handler will be called soon to look at our request.
	 */
	if (!timer_pending(&ppd->led_override_timer)) {
		timer_setup(&ppd->led_override_timer, run_led_override, 0);
		ppd->led_override_timer.expires = jiffies + 1;
		add_timer(&ppd->led_override_timer);
		atomic_set(&ppd->led_override_timer_active, 1);
		/* Ensure the atomic_set is visible to all CPUs */
		smp_wmb();
	}
}