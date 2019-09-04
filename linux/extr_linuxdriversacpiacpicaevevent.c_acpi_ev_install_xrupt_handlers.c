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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ev_init_global_lock_handler () ; 
 int /*<<< orphan*/  acpi_ev_install_sci_handler () ; 
 int /*<<< orphan*/  acpi_gbl_events_initialized ; 
 scalar_t__ acpi_gbl_reduced_hardware ; 
 int /*<<< orphan*/  ev_install_xrupt_handlers ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ev_install_xrupt_handlers(void)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_install_xrupt_handlers);

	/* If Hardware Reduced flag is set, there is no ACPI h/w */

	if (acpi_gbl_reduced_hardware) {
		return_ACPI_STATUS(AE_OK);
	}

	/* Install the SCI handler */

	status = acpi_ev_install_sci_handler();
	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Unable to install System Control Interrupt handler"));
		return_ACPI_STATUS(status);
	}

	/* Install the handler for the Global Lock */

	status = acpi_ev_init_global_lock_handler();
	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Unable to initialize Global Lock handler"));
		return_ACPI_STATUS(status);
	}

	acpi_gbl_events_initialized = TRUE;
	return_ACPI_STATUS(status);
}