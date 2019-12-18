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
struct intel_wakeref_auto {int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; int /*<<< orphan*/  count; int /*<<< orphan*/  rpm; int /*<<< orphan*/  wakeref; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_WAKEREF_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (int /*<<< orphan*/ ) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_get_if_in_use (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wakeref_auto_timeout (int /*<<< orphan*/ *) ; 

void intel_wakeref_auto(struct intel_wakeref_auto *wf, unsigned long timeout)
{
	unsigned long flags;

	if (!timeout) {
		if (del_timer_sync(&wf->timer))
			wakeref_auto_timeout(&wf->timer);
		return;
	}

	/* Our mission is that we only extend an already active wakeref */
	assert_rpm_wakelock_held(wf->rpm);

	if (!refcount_inc_not_zero(&wf->count)) {
		spin_lock_irqsave(&wf->lock, flags);
		if (!refcount_inc_not_zero(&wf->count)) {
			INTEL_WAKEREF_BUG_ON(wf->wakeref);
			wf->wakeref = intel_runtime_pm_get_if_in_use(wf->rpm);
			refcount_set(&wf->count, 1);
		}
		spin_unlock_irqrestore(&wf->lock, flags);
	}

	/*
	 * If we extend a pending timer, we will only get a single timer
	 * callback and so need to cancel the local inc by running the
	 * elided callback to keep the wf->count balanced.
	 */
	if (mod_timer(&wf->timer, jiffies + timeout))
		wakeref_auto_timeout(&wf->timer);
}