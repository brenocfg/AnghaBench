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
struct wakeup_source {int active; int /*<<< orphan*/  entry; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  events_lock ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_wakeup_timer_fn ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_sources ; 

void wakeup_source_add(struct wakeup_source *ws)
{
	unsigned long flags;

	if (WARN_ON(!ws))
		return;

	spin_lock_init(&ws->lock);
	timer_setup(&ws->timer, pm_wakeup_timer_fn, 0);
	ws->active = false;

	raw_spin_lock_irqsave(&events_lock, flags);
	list_add_rcu(&ws->entry, &wakeup_sources);
	raw_spin_unlock_irqrestore(&events_lock, flags);
}