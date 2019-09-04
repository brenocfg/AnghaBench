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
struct timer_list {scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ __round_jiffies_up (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  add_timer_on (struct timer_list*,unsigned int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int wd_timer_period_ms ; 

__attribute__((used)) static void wd_timer_reset(unsigned int cpu, struct timer_list *t)
{
	t->expires = jiffies + msecs_to_jiffies(wd_timer_period_ms);
	if (wd_timer_period_ms > 1000)
		t->expires = __round_jiffies_up(t->expires, cpu);
	add_timer_on(t, cpu);
}