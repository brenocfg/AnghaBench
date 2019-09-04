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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 size_t ACPI_S_STATES_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_enter_sleep_state (size_t) ; 
 int /*<<< orphan*/  acpi_enter_sleep_state_prep (size_t) ; 
 int /*<<< orphan*/  acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * acpi_gbl_sleep_state_names ; 
 int /*<<< orphan*/  acpi_get_sleep_type_data (size_t,size_t*,size_t*) ; 
 int /*<<< orphan*/  acpi_leave_sleep_state (size_t) ; 
 int /*<<< orphan*/  acpi_leave_sleep_state_prep (size_t) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,size_t,...) ; 

__attribute__((used)) static void acpi_db_do_one_sleep_state(u8 sleep_state)
{
	acpi_status status;
	u8 sleep_type_a;
	u8 sleep_type_b;

	/* Validate parameter */

	if (sleep_state > ACPI_S_STATES_MAX) {
		acpi_os_printf("Sleep state %d out of range (%d max)\n",
			       sleep_state, ACPI_S_STATES_MAX);
		return;
	}

	acpi_os_printf("\n---- Invoking sleep state S%d (%s):\n",
		       sleep_state, acpi_gbl_sleep_state_names[sleep_state]);

	/* Get the values for the sleep type registers (for display only) */

	status =
	    acpi_get_sleep_type_data(sleep_state, &sleep_type_a, &sleep_type_b);
	if (ACPI_FAILURE(status)) {
		acpi_os_printf("Could not evaluate [%s] method, %s\n",
			       acpi_gbl_sleep_state_names[sleep_state],
			       acpi_format_exception(status));
		return;
	}

	acpi_os_printf
	    ("Register values for sleep state S%d: Sleep-A: %.2X, Sleep-B: %.2X\n",
	     sleep_state, sleep_type_a, sleep_type_b);

	/* Invoke the various sleep/wake interfaces */

	acpi_os_printf("**** Sleep: Prepare to sleep (S%d) ****\n",
		       sleep_state);
	status = acpi_enter_sleep_state_prep(sleep_state);
	if (ACPI_FAILURE(status)) {
		goto error_exit;
	}

	acpi_os_printf("**** Sleep: Going to sleep (S%d) ****\n", sleep_state);
	status = acpi_enter_sleep_state(sleep_state);
	if (ACPI_FAILURE(status)) {
		goto error_exit;
	}

	acpi_os_printf("**** Wake: Prepare to return from sleep (S%d) ****\n",
		       sleep_state);
	status = acpi_leave_sleep_state_prep(sleep_state);
	if (ACPI_FAILURE(status)) {
		goto error_exit;
	}

	acpi_os_printf("**** Wake: Return from sleep (S%d) ****\n",
		       sleep_state);
	status = acpi_leave_sleep_state(sleep_state);
	if (ACPI_FAILURE(status)) {
		goto error_exit;
	}

	return;

error_exit:
	ACPI_EXCEPTION((AE_INFO, status, "During invocation of sleep state S%d",
			sleep_state));
}