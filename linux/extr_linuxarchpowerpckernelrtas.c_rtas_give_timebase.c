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
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ get_tb () ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rtas_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtas_token (char*) ; 
 scalar_t__ timebase ; 
 int /*<<< orphan*/  timebase_lock ; 

void rtas_give_timebase(void)
{
	unsigned long flags;

	local_irq_save(flags);
	hard_irq_disable();
	arch_spin_lock(&timebase_lock);
	rtas_call(rtas_token("freeze-time-base"), 0, 1, NULL);
	timebase = get_tb();
	arch_spin_unlock(&timebase_lock);

	while (timebase)
		barrier();
	rtas_call(rtas_token("thaw-time-base"), 0, 1, NULL);
	local_irq_restore(flags);
}