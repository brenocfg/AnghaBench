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
 int dim_get_lock_state () ; 
 int /*<<< orphan*/  dim_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool dim2_sysfs_get_state_cb(void)
{
	bool state;
	unsigned long flags;

	spin_lock_irqsave(&dim_lock, flags);
	state = dim_get_lock_state();
	spin_unlock_irqrestore(&dim_lock, flags);

	return state;
}