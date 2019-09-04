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
struct acpi_walk_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_gbl_cm_single_step ; 
 scalar_t__ acpi_gbl_db_thread_id ; 
 scalar_t__ acpi_os_get_thread_id () ; 
 int /*<<< orphan*/  acpi_os_printf (char*) ; 

void acpi_db_signal_break_point(struct acpi_walk_state *walk_state)
{

#ifndef ACPI_APPLICATION
	if (acpi_gbl_db_thread_id != acpi_os_get_thread_id()) {
		return;
	}
#endif

	/*
	 * Set the single-step flag. This will cause the debugger (if present)
	 * to break to the console within the AML debugger at the start of the
	 * next AML instruction.
	 */
	acpi_gbl_cm_single_step = TRUE;
	acpi_os_printf("**break** Executed AML BreakPoint opcode\n");
}