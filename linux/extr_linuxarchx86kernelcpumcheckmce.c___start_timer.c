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
struct timer_list {int /*<<< orphan*/  expires; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (unsigned long) ; 
 scalar_t__ time_before (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pending (struct timer_list*) ; 

__attribute__((used)) static void __start_timer(struct timer_list *t, unsigned long interval)
{
	unsigned long when = jiffies + interval;
	unsigned long flags;

	local_irq_save(flags);

	if (!timer_pending(t) || time_before(when, t->expires))
		mod_timer(t, round_jiffies(when));

	local_irq_restore(flags);
}