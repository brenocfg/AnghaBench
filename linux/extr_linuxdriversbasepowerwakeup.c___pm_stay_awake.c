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
struct wakeup_source {int /*<<< orphan*/  lock; scalar_t__ timer_expires; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wakeup_source_report_event (struct wakeup_source*,int) ; 

void __pm_stay_awake(struct wakeup_source *ws)
{
	unsigned long flags;

	if (!ws)
		return;

	spin_lock_irqsave(&ws->lock, flags);

	wakeup_source_report_event(ws, false);
	del_timer(&ws->timer);
	ws->timer_expires = 0;

	spin_unlock_irqrestore(&ws->lock, flags);
}