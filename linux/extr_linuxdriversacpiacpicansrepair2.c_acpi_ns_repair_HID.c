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
struct TYPE_4__ {scalar_t__ length; char* pointer; } ;
struct TYPE_3__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_2__ string; TYPE_1__ common; } ;
struct acpi_evaluate_info {int /*<<< orphan*/  full_pathname; int /*<<< orphan*/  return_flags; int /*<<< orphan*/  node_flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_OBJECT_REPAIRED ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 union acpi_operand_object* acpi_ut_create_string_object (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ns_repair_HID ; 
 scalar_t__ toupper (int) ; 

__attribute__((used)) static acpi_status
acpi_ns_repair_HID(struct acpi_evaluate_info *info,
		   union acpi_operand_object **return_object_ptr)
{
	union acpi_operand_object *return_object = *return_object_ptr;
	union acpi_operand_object *new_string;
	char *source;
	char *dest;

	ACPI_FUNCTION_NAME(ns_repair_HID);

	/* We only care about string _HID objects (not integers) */

	if (return_object->common.type != ACPI_TYPE_STRING) {
		return (AE_OK);
	}

	if (return_object->string.length == 0) {
		ACPI_WARN_PREDEFINED((AE_INFO,
				      info->full_pathname, info->node_flags,
				      "Invalid zero-length _HID or _CID string"));

		/* Return AE_OK anyway, let driver handle it */

		info->return_flags |= ACPI_OBJECT_REPAIRED;
		return (AE_OK);
	}

	/* It is simplest to always create a new string object */

	new_string = acpi_ut_create_string_object(return_object->string.length);
	if (!new_string) {
		return (AE_NO_MEMORY);
	}

	/*
	 * Remove a leading asterisk if present. For some unknown reason, there
	 * are many machines in the field that contains IDs like this.
	 *
	 * Examples: "*PNP0C03", "*ACPI0003"
	 */
	source = return_object->string.pointer;
	if (*source == '*') {
		source++;
		new_string->string.length--;

		ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
				  "%s: Removed invalid leading asterisk\n",
				  info->full_pathname));
	}

	/*
	 * Copy and uppercase the string. From the ACPI 5.0 specification:
	 *
	 * A valid PNP ID must be of the form "AAA####" where A is an uppercase
	 * letter and # is a hex digit. A valid ACPI ID must be of the form
	 * "NNNN####" where N is an uppercase letter or decimal digit, and
	 * # is a hex digit.
	 */
	for (dest = new_string->string.pointer; *source; dest++, source++) {
		*dest = (char)toupper((int)*source);
	}

	acpi_ut_remove_reference(return_object);
	*return_object_ptr = new_string;
	return (AE_OK);
}