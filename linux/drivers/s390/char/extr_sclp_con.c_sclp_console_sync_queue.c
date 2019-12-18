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

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_con_lock ; 
 scalar_t__ sclp_con_queue_running ; 
 int /*<<< orphan*/  sclp_con_timer ; 
 int /*<<< orphan*/  sclp_sync_wait () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sclp_console_sync_queue(void)
{
	unsigned long flags;

	spin_lock_irqsave(&sclp_con_lock, flags);
	if (timer_pending(&sclp_con_timer))
		del_timer(&sclp_con_timer);
	while (sclp_con_queue_running) {
		spin_unlock_irqrestore(&sclp_con_lock, flags);
		sclp_sync_wait();
		spin_lock_irqsave(&sclp_con_lock, flags);
	}
	spin_unlock_irqrestore(&sclp_con_lock, flags);
}