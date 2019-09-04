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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ clockevent_state_oneshot (struct clock_event_device*) ; 
 scalar_t__ clockevent_state_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  disable_mfgpt0_counter () ; 
 int /*<<< orphan*/  mfgpt_lock ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mfgpt_timer_shutdown(struct clock_event_device *evt)
{
	if (clockevent_state_periodic(evt) || clockevent_state_oneshot(evt)) {
		raw_spin_lock(&mfgpt_lock);
		disable_mfgpt0_counter();
		raw_spin_unlock(&mfgpt_lock);
	}

	return 0;
}