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
 int /*<<< orphan*/  DSSWARN (char*) ; 
 int /*<<< orphan*/  data_lock ; 
 int extra_info_update_ongoing () ; 
 int /*<<< orphan*/  extra_updated_completion ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void wait_pending_extra_info_updates(void)
{
	bool updating;
	unsigned long flags;
	unsigned long t;
	int r;

	spin_lock_irqsave(&data_lock, flags);

	updating = extra_info_update_ongoing();

	if (!updating) {
		spin_unlock_irqrestore(&data_lock, flags);
		return;
	}

	init_completion(&extra_updated_completion);

	spin_unlock_irqrestore(&data_lock, flags);

	t = msecs_to_jiffies(500);
	r = wait_for_completion_timeout(&extra_updated_completion, t);
	if (r == 0)
		DSSWARN("timeout in wait_pending_extra_info_updates\n");
}