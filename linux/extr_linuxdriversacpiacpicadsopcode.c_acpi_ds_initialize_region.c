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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ev_initialize_region (union acpi_operand_object*) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (int /*<<< orphan*/ ) ; 

acpi_status acpi_ds_initialize_region(acpi_handle obj_handle)
{
	union acpi_operand_object *obj_desc;
	acpi_status status;

	obj_desc = acpi_ns_get_attached_object(obj_handle);

	/* Namespace is NOT locked */

	status = acpi_ev_initialize_region(obj_desc);
	return (status);
}