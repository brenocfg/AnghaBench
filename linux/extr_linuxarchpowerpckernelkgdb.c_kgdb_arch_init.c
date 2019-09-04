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
 int /*<<< orphan*/  __debugger ; 
 int /*<<< orphan*/  __debugger_bpt ; 
 int /*<<< orphan*/  __debugger_break_match ; 
 int /*<<< orphan*/  __debugger_fault_handler ; 
 int /*<<< orphan*/  __debugger_iabr_match ; 
 int /*<<< orphan*/  __debugger_ipi ; 
 int /*<<< orphan*/  __debugger_sstep ; 
 int /*<<< orphan*/  kgdb_break_match ; 
 int /*<<< orphan*/  kgdb_call_nmi_hook ; 
 int /*<<< orphan*/  kgdb_debugger ; 
 int /*<<< orphan*/  kgdb_handle_breakpoint ; 
 int /*<<< orphan*/  kgdb_iabr_match ; 
 int /*<<< orphan*/  kgdb_not_implemented ; 
 int /*<<< orphan*/  kgdb_singlestep ; 
 int /*<<< orphan*/  old__debugger ; 
 int /*<<< orphan*/  old__debugger_bpt ; 
 int /*<<< orphan*/  old__debugger_break_match ; 
 int /*<<< orphan*/  old__debugger_fault_handler ; 
 int /*<<< orphan*/  old__debugger_iabr_match ; 
 int /*<<< orphan*/  old__debugger_ipi ; 
 int /*<<< orphan*/  old__debugger_sstep ; 

int kgdb_arch_init(void)
{
	old__debugger_ipi = __debugger_ipi;
	old__debugger = __debugger;
	old__debugger_bpt = __debugger_bpt;
	old__debugger_sstep = __debugger_sstep;
	old__debugger_iabr_match = __debugger_iabr_match;
	old__debugger_break_match = __debugger_break_match;
	old__debugger_fault_handler = __debugger_fault_handler;

	__debugger_ipi = kgdb_call_nmi_hook;
	__debugger = kgdb_debugger;
	__debugger_bpt = kgdb_handle_breakpoint;
	__debugger_sstep = kgdb_singlestep;
	__debugger_iabr_match = kgdb_iabr_match;
	__debugger_break_match = kgdb_break_match;
	__debugger_fault_handler = kgdb_not_implemented;

	return 0;
}