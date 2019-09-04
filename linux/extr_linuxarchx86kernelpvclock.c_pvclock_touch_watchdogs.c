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
 int /*<<< orphan*/  clocksource_touch_watchdog () ; 
 int /*<<< orphan*/  rcu_cpu_stall_reset () ; 
 int /*<<< orphan*/  reset_hung_task_detector () ; 
 int /*<<< orphan*/  touch_softlockup_watchdog_sync () ; 

void pvclock_touch_watchdogs(void)
{
	touch_softlockup_watchdog_sync();
	clocksource_touch_watchdog();
	rcu_cpu_stall_reset();
	reset_hung_task_detector();
}