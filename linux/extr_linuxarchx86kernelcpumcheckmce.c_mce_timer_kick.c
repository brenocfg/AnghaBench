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
 int /*<<< orphan*/  __start_timer (struct timer_list*,unsigned long) ; 
 unsigned long __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mce_next_interval ; 
 int /*<<< orphan*/  mce_timer ; 
 struct timer_list* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void mce_timer_kick(unsigned long interval)
{
	struct timer_list *t = this_cpu_ptr(&mce_timer);
	unsigned long iv = __this_cpu_read(mce_next_interval);

	__start_timer(t, interval);

	if (interval < iv)
		__this_cpu_write(mce_next_interval, interval);
}