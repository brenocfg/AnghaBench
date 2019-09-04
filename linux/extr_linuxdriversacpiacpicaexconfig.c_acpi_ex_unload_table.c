#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
union acpi_operand_object {TYPE_2__ common; TYPE_1__ reference; } ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 int /*<<< orphan*/  acpi_tb_unload_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_unload_table ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_unload_table(union acpi_operand_object *ddb_handle)
{
	acpi_status status = AE_OK;
	union acpi_operand_object *table_desc = ddb_handle;
	u32 table_index;

	ACPI_FUNCTION_TRACE(ex_unload_table);

	/*
	 * Temporarily emit a warning so that the ASL for the machine can be
	 * hopefully obtained. This is to say that the Unload() operator is
	 * extremely rare if not completely unused.
	 */
	ACPI_WARNING((AE_INFO, "Received request to unload an ACPI table"));

	/*
	 * May 2018: Unload is no longer supported for the following reasons:
	 * 1) A correct implementation on some hosts may not be possible.
	 * 2) Other ACPI implementations do not correctly/fully support it.
	 * 3) It requires host device driver support which does not exist.
	 *    (To properly support namespace unload out from underneath.)
	 * 4) This AML operator has never been seen in the field.
	 */
	ACPI_EXCEPTION((AE_INFO, AE_NOT_IMPLEMENTED,
			"AML Unload operator is not supported"));

	/*
	 * Validate the handle
	 * Although the handle is partially validated in acpi_ex_reconfiguration()
	 * when it calls acpi_ex_resolve_operands(), the handle is more completely
	 * validated here.
	 *
	 * Handle must be a valid operand object of type reference. Also, the
	 * ddb_handle must still be marked valid (table has not been previously
	 * unloaded)
	 */
	if ((!ddb_handle) ||
	    (ACPI_GET_DESCRIPTOR_TYPE(ddb_handle) != ACPI_DESC_TYPE_OPERAND) ||
	    (ddb_handle->common.type != ACPI_TYPE_LOCAL_REFERENCE) ||
	    (!(ddb_handle->common.flags & AOPOBJ_DATA_VALID))) {
		return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	}

	/* Get the table index from the ddb_handle */

	table_index = table_desc->reference.value;

	/*
	 * Release the interpreter lock so that the table lock won't have
	 * strict order requirement against it.
	 */
	acpi_ex_exit_interpreter();
	status = acpi_tb_unload_table(table_index);
	acpi_ex_enter_interpreter();

	/*
	 * Invalidate the handle. We do this because the handle may be stored
	 * in a named object and may not be actually deleted until much later.
	 */
	if (ACPI_SUCCESS(status)) {
		ddb_handle->common.flags &= ~AOPOBJ_DATA_VALID;
	}
	return_ACPI_STATUS(status);
}