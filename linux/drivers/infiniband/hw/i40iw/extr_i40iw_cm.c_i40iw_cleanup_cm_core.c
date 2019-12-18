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
struct i40iw_cm_core {scalar_t__ disconn_wq; scalar_t__ event_wq; int /*<<< orphan*/  ht_lock; int /*<<< orphan*/  tcp_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

void i40iw_cleanup_cm_core(struct i40iw_cm_core *cm_core)
{
	unsigned long flags;

	if (!cm_core)
		return;

	spin_lock_irqsave(&cm_core->ht_lock, flags);
	if (timer_pending(&cm_core->tcp_timer))
		del_timer_sync(&cm_core->tcp_timer);
	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	if (cm_core->event_wq)
		destroy_workqueue(cm_core->event_wq);
	if (cm_core->disconn_wq)
		destroy_workqueue(cm_core->disconn_wq);
}