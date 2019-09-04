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
struct vtimer_list {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_timer_lock ; 
 int /*<<< orphan*/  vtimer_pending (struct vtimer_list*) ; 

int del_virt_timer(struct vtimer_list *timer)
{
	unsigned long flags;

	if (!vtimer_pending(timer))
		return 0;
	spin_lock_irqsave(&virt_timer_lock, flags);
	list_del_init(&timer->entry);
	spin_unlock_irqrestore(&virt_timer_lock, flags);
	return 1;
}