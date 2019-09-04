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
 int /*<<< orphan*/  __do_restart ; 
 int /*<<< orphan*/  debug_locks_off () ; 
 int /*<<< orphan*/  lgr_info_log () ; 
 int /*<<< orphan*/  smp_call_online_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracing_off () ; 

void do_restart(void)
{
	tracing_off();
	debug_locks_off();
	lgr_info_log();
	smp_call_online_cpu(__do_restart, NULL);
}