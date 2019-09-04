#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  os_semaphore; } ;
union acpi_operand_object {TYPE_1__ event; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_semaphore ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  ACPI_NO_UNIT_LIMIT ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_os_create_semaphore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_delete_semaphore (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_system_reset_event(union acpi_operand_object *obj_desc)
{
	acpi_status status = AE_OK;
	acpi_semaphore temp_semaphore;

	ACPI_FUNCTION_ENTRY();

	/*
	 * We are going to simply delete the existing semaphore and
	 * create a new one!
	 */
	status =
	    acpi_os_create_semaphore(ACPI_NO_UNIT_LIMIT, 0, &temp_semaphore);
	if (ACPI_SUCCESS(status)) {
		(void)acpi_os_delete_semaphore(obj_desc->event.os_semaphore);
		obj_desc->event.os_semaphore = temp_semaphore;
	}

	return (status);
}