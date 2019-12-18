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
struct ci_hdrc {int enabled_otg_timer_bits; int next_otg_timer; int /*<<< orphan*/  lock; int /*<<< orphan*/ * hr_timeouts; int /*<<< orphan*/  otg_fsm_hrtimer; } ;
typedef  enum otg_fsm_timer { ____Placeholder_otg_fsm_timer } otg_fsm_timer ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 unsigned long MSEC_PER_SEC ; 
 unsigned long NSEC_PER_MSEC ; 
 int NUM_OTG_FSM_TIMERS ; 
 int /*<<< orphan*/  hrtimer_start_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_set (unsigned long,unsigned long) ; 
 unsigned long* otg_timer_ms ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ci_otg_add_timer(struct ci_hdrc *ci, enum otg_fsm_timer t)
{
	unsigned long flags, timer_sec, timer_nsec;

	if (t >= NUM_OTG_FSM_TIMERS)
		return;

	spin_lock_irqsave(&ci->lock, flags);
	timer_sec = otg_timer_ms[t] / MSEC_PER_SEC;
	timer_nsec = (otg_timer_ms[t] % MSEC_PER_SEC) * NSEC_PER_MSEC;
	ci->hr_timeouts[t] = ktime_add(ktime_get(),
				ktime_set(timer_sec, timer_nsec));
	ci->enabled_otg_timer_bits |= (1 << t);
	if ((ci->next_otg_timer == NUM_OTG_FSM_TIMERS) ||
			ktime_after(ci->hr_timeouts[ci->next_otg_timer],
						ci->hr_timeouts[t])) {
			ci->next_otg_timer = t;
			hrtimer_start_range_ns(&ci->otg_fsm_hrtimer,
					ci->hr_timeouts[t], NSEC_PER_MSEC,
							HRTIMER_MODE_ABS);
	}
	spin_unlock_irqrestore(&ci->lock, flags);
}