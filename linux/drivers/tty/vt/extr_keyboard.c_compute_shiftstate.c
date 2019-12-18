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
 int /*<<< orphan*/  do_compute_shiftstate () ; 
 int /*<<< orphan*/  kbd_event_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void compute_shiftstate(void)
{
	unsigned long flags;
	spin_lock_irqsave(&kbd_event_lock, flags);
	do_compute_shiftstate();
	spin_unlock_irqrestore(&kbd_event_lock, flags);
}