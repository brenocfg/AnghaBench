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
struct wakeup_source {int /*<<< orphan*/  lock; int /*<<< orphan*/  expire_count; scalar_t__ timer_expires; scalar_t__ active; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct wakeup_source* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  wakeup_source_deactivate (struct wakeup_source*) ; 
 struct wakeup_source* ws ; 

__attribute__((used)) static void pm_wakeup_timer_fn(struct timer_list *t)
{
	struct wakeup_source *ws = from_timer(ws, t, timer);
	unsigned long flags;

	spin_lock_irqsave(&ws->lock, flags);

	if (ws->active && ws->timer_expires
	    && time_after_eq(jiffies, ws->timer_expires)) {
		wakeup_source_deactivate(ws);
		ws->expire_count++;
	}

	spin_unlock_irqrestore(&ws->lock, flags);
}