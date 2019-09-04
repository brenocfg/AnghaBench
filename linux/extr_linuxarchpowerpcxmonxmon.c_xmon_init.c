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
 int /*<<< orphan*/ * __debugger ; 
 int /*<<< orphan*/ * __debugger_bpt ; 
 int /*<<< orphan*/ * __debugger_break_match ; 
 int /*<<< orphan*/ * __debugger_fault_handler ; 
 int /*<<< orphan*/ * __debugger_iabr_match ; 
 int /*<<< orphan*/ * __debugger_ipi ; 
 int /*<<< orphan*/ * __debugger_sstep ; 
 int /*<<< orphan*/ * xmon ; 
 int /*<<< orphan*/ * xmon_bpt ; 
 int /*<<< orphan*/ * xmon_break_match ; 
 int /*<<< orphan*/ * xmon_fault_handler ; 
 int /*<<< orphan*/ * xmon_iabr_match ; 
 int /*<<< orphan*/ * xmon_ipi ; 
 int /*<<< orphan*/ * xmon_sstep ; 

__attribute__((used)) static void xmon_init(int enable)
{
	if (enable) {
		__debugger = xmon;
		__debugger_ipi = xmon_ipi;
		__debugger_bpt = xmon_bpt;
		__debugger_sstep = xmon_sstep;
		__debugger_iabr_match = xmon_iabr_match;
		__debugger_break_match = xmon_break_match;
		__debugger_fault_handler = xmon_fault_handler;

#ifdef CONFIG_PPC_PSERIES
		/*
		 * Get the token here to avoid trying to get a lock
		 * during the crash, causing a deadlock.
		 */
		set_indicator_token = rtas_token("set-indicator");
#endif
	} else {
		__debugger = NULL;
		__debugger_ipi = NULL;
		__debugger_bpt = NULL;
		__debugger_sstep = NULL;
		__debugger_iabr_match = NULL;
		__debugger_break_match = NULL;
		__debugger_fault_handler = NULL;
	}
}