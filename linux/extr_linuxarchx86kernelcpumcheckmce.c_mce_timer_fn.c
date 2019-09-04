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
 int HZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __start_timer (struct timer_list*,unsigned long) ; 
 unsigned long __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 
 int check_interval ; 
 int /*<<< orphan*/  cpu_info ; 
 int /*<<< orphan*/  machine_check_poll (int /*<<< orphan*/ ,struct timer_list*) ; 
 unsigned long max (unsigned long,unsigned long) ; 
 unsigned long mce_adjust_timer (unsigned long) ; 
 scalar_t__ mce_available (struct timer_list*) ; 
 scalar_t__ mce_intel_cmci_poll () ; 
 int /*<<< orphan*/  mce_next_interval ; 
 scalar_t__ mce_notify_irq () ; 
 int /*<<< orphan*/  mce_poll_banks ; 
 int /*<<< orphan*/  mce_timer ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_relative (int) ; 
 struct timer_list* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mce_timer_fn(struct timer_list *t)
{
	struct timer_list *cpu_t = this_cpu_ptr(&mce_timer);
	unsigned long iv;

	WARN_ON(cpu_t != t);

	iv = __this_cpu_read(mce_next_interval);

	if (mce_available(this_cpu_ptr(&cpu_info))) {
		machine_check_poll(0, this_cpu_ptr(&mce_poll_banks));

		if (mce_intel_cmci_poll()) {
			iv = mce_adjust_timer(iv);
			goto done;
		}
	}

	/*
	 * Alert userspace if needed. If we logged an MCE, reduce the polling
	 * interval, otherwise increase the polling interval.
	 */
	if (mce_notify_irq())
		iv = max(iv / 2, (unsigned long) HZ/100);
	else
		iv = min(iv * 2, round_jiffies_relative(check_interval * HZ));

done:
	__this_cpu_write(mce_next_interval, iv);
	__start_timer(t, iv);
}