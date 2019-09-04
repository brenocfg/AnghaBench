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
 int /*<<< orphan*/  del_timer_sync (struct timer_list*) ; 
 struct timer_list* per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  wd_timer ; 

__attribute__((used)) static void stop_watchdog_timer_on(unsigned int cpu)
{
	struct timer_list *t = per_cpu_ptr(&wd_timer, cpu);

	del_timer_sync(t);
}