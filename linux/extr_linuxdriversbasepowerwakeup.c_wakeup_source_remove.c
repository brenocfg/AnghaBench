#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * function; } ;
struct wakeup_source {TYPE_1__ timer; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  events_lock ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_srcu ; 

void wakeup_source_remove(struct wakeup_source *ws)
{
	unsigned long flags;

	if (WARN_ON(!ws))
		return;

	raw_spin_lock_irqsave(&events_lock, flags);
	list_del_rcu(&ws->entry);
	raw_spin_unlock_irqrestore(&events_lock, flags);
	synchronize_srcu(&wakeup_srcu);

	del_timer_sync(&ws->timer);
	/*
	 * Clear timer.function to make wakeup_source_not_registered() treat
	 * this wakeup source as not registered.
	 */
	ws->timer.function = NULL;
}