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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_MAX_SLEEP ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 int /*<<< orphan*/  acpi_os_sleep (scalar_t__) ; 

acpi_status acpi_ex_system_do_sleep(u64 how_long)
{
	ACPI_FUNCTION_ENTRY();

	/* Since this thread will sleep, we must release the interpreter */

	acpi_ex_exit_interpreter();

	/*
	 * For compatibility with other ACPI implementations and to prevent
	 * accidental deep sleeps, limit the sleep time to something reasonable.
	 */
	if (how_long > ACPI_MAX_SLEEP) {
		how_long = ACPI_MAX_SLEEP;
	}

	acpi_os_sleep(how_long);

	/* And now we must get the interpreter again */

	acpi_ex_enter_interpreter();
	return (AE_OK);
}