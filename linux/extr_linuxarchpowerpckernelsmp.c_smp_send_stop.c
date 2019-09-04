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
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_this_cpu ; 

void smp_send_stop(void)
{
	static bool stopped = false;

	/*
	 * Prevent waiting on csd lock from a previous smp_send_stop.
	 * This is racy, but in general callers try to do the right
	 * thing and only fire off one smp_send_stop (e.g., see
	 * kernel/panic.c)
	 */
	if (stopped)
		return;

	stopped = true;

	smp_call_function(stop_this_cpu, NULL, 0);
}