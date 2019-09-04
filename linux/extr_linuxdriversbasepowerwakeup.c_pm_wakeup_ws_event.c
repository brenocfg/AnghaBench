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
struct wakeup_source {unsigned long timer_expires; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wakeup_source_deactivate (struct wakeup_source*) ; 
 int /*<<< orphan*/  wakeup_source_report_event (struct wakeup_source*,int) ; 

void pm_wakeup_ws_event(struct wakeup_source *ws, unsigned int msec, bool hard)
{
	unsigned long flags;
	unsigned long expires;

	if (!ws)
		return;

	spin_lock_irqsave(&ws->lock, flags);

	wakeup_source_report_event(ws, hard);

	if (!msec) {
		wakeup_source_deactivate(ws);
		goto unlock;
	}

	expires = jiffies + msecs_to_jiffies(msec);
	if (!expires)
		expires = 1;

	if (!ws->timer_expires || time_after(expires, ws->timer_expires)) {
		mod_timer(&ws->timer, expires);
		ws->timer_expires = expires;
	}

 unlock:
	spin_unlock_irqrestore(&ws->lock, flags);
}