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
struct hfi1_ctxtdata {void* aspm_ts_timer_sched; int aspm_enabled; int /*<<< orphan*/  aspm_lock; int /*<<< orphan*/  aspm_timer; int /*<<< orphan*/  dd; void* aspm_ts_last_intr; int /*<<< orphan*/  aspm_intr_enable; } ;
typedef  void* ktime_t ;

/* Variables and functions */
 int ASPM_RESCHED_TIMER_MS ; 
 int /*<<< orphan*/  ASPM_TIMER_MS ; 
 int ASPM_TRIGGER_NS ; 
 int NSEC_PER_MSEC ; 
 int /*<<< orphan*/  aspm_disable_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 void* ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (void*,void*) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void __aspm_ctx_disable(struct hfi1_ctxtdata *rcd)
{
	bool restart_timer;
	bool close_interrupts;
	unsigned long flags;
	ktime_t now, prev;

	spin_lock_irqsave(&rcd->aspm_lock, flags);
	/* PSM contexts are open */
	if (!rcd->aspm_intr_enable)
		goto unlock;

	prev = rcd->aspm_ts_last_intr;
	now = ktime_get();
	rcd->aspm_ts_last_intr = now;

	/* An interrupt pair close together in time */
	close_interrupts = ktime_to_ns(ktime_sub(now, prev)) < ASPM_TRIGGER_NS;

	/* Don't push out our timer till this much time has elapsed */
	restart_timer = ktime_to_ns(ktime_sub(now, rcd->aspm_ts_timer_sched)) >
				    ASPM_RESCHED_TIMER_MS * NSEC_PER_MSEC;
	restart_timer = restart_timer && close_interrupts;

	/* Disable ASPM and schedule timer */
	if (rcd->aspm_enabled && close_interrupts) {
		aspm_disable_inc(rcd->dd);
		rcd->aspm_enabled = false;
		restart_timer = true;
	}

	if (restart_timer) {
		mod_timer(&rcd->aspm_timer,
			  jiffies + msecs_to_jiffies(ASPM_TIMER_MS));
		rcd->aspm_ts_timer_sched = now;
	}
unlock:
	spin_unlock_irqrestore(&rcd->aspm_lock, flags);
}