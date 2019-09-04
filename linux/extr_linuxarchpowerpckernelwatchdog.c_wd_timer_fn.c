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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int smp_processor_id () ; 
 int /*<<< orphan*/  watchdog_timer_interrupt (int) ; 
 int /*<<< orphan*/  wd_timer_reset (int,struct timer_list*) ; 

__attribute__((used)) static void wd_timer_fn(struct timer_list *t)
{
	int cpu = smp_processor_id();

	watchdog_timer_interrupt(cpu);

	wd_timer_reset(cpu, t);
}