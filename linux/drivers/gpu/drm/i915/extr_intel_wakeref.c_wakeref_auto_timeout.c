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
struct intel_wakeref_auto {int /*<<< orphan*/  rpm; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeref; int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  fetch_and_zero (int /*<<< orphan*/ *) ; 
 struct intel_wakeref_auto* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 struct intel_wakeref_auto* wf ; 

__attribute__((used)) static void wakeref_auto_timeout(struct timer_list *t)
{
	struct intel_wakeref_auto *wf = from_timer(wf, t, timer);
	intel_wakeref_t wakeref;
	unsigned long flags;

	if (!refcount_dec_and_lock_irqsave(&wf->count, &wf->lock, &flags))
		return;

	wakeref = fetch_and_zero(&wf->wakeref);
	spin_unlock_irqrestore(&wf->lock, flags);

	intel_runtime_pm_put(wf->rpm, wakeref);
}