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
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  acpi_handle_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 

acpi_status acpi_evaluate_lck(acpi_handle handle, int lock)
{
	acpi_status status;

	status = acpi_execute_simple_method(handle, "_LCK", !!lock);
	if (ACPI_FAILURE(status) && status != AE_NOT_FOUND) {
		if (lock)
			acpi_handle_warn(handle,
				"Locking device failed (0x%x)\n", status);
		else
			acpi_handle_warn(handle,
				"Unlocking device failed (0x%x)\n", status);
	}

	return status;
}