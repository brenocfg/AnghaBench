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
 int /*<<< orphan*/  clear_sched_clock_stable () ; 
 int /*<<< orphan*/  clocksource_mark_unstable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clocksource_tsc ; 
 int /*<<< orphan*/  clocksource_tsc_early ; 
 int /*<<< orphan*/  disable_sched_clock_irqtime () ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int tsc_unstable ; 
 scalar_t__ using_native_sched_clock () ; 

void mark_tsc_unstable(char *reason)
{
	if (tsc_unstable)
		return;

	tsc_unstable = 1;
	if (using_native_sched_clock())
		clear_sched_clock_stable();
	disable_sched_clock_irqtime();
	pr_info("Marking TSC unstable due to %s\n", reason);

	clocksource_mark_unstable(&clocksource_tsc_early);
	clocksource_mark_unstable(&clocksource_tsc);
}