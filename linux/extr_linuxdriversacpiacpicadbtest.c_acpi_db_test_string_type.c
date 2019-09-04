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
struct TYPE_2__ {int length; char* pointer; } ;
union acpi_object {TYPE_1__ string; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  acpi_db_read_from_object (struct acpi_namespace_node*,int /*<<< orphan*/ ,union acpi_object**) ; 
 int /*<<< orphan*/  acpi_db_write_to_object (struct acpi_namespace_node*,union acpi_object*) ; 
 int /*<<< orphan*/  acpi_os_free (union acpi_object*) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strlen (char*) ; 

__attribute__((used)) static acpi_status
acpi_db_test_string_type(struct acpi_namespace_node *node, u32 byte_length)
{
	union acpi_object *temp1 = NULL;
	union acpi_object *temp2 = NULL;
	union acpi_object *temp3 = NULL;
	char *value_to_write = "Test String from AML Debugger";
	union acpi_object write_value;
	acpi_status status;

	/* Read the original value */

	status = acpi_db_read_from_object(node, ACPI_TYPE_STRING, &temp1);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	acpi_os_printf(" (%4.4X/%3.3X) \"%s\"", (temp1->string.length * 8),
		       temp1->string.length, temp1->string.pointer);

	/* Write a new value */

	write_value.type = ACPI_TYPE_STRING;
	write_value.string.length = strlen(value_to_write);
	write_value.string.pointer = value_to_write;

	status = acpi_db_write_to_object(node, &write_value);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	/* Ensure that we can read back the new value */

	status = acpi_db_read_from_object(node, ACPI_TYPE_STRING, &temp2);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	if (strcmp(temp2->string.pointer, value_to_write)) {
		acpi_os_printf(" MISMATCH 2: %s, expecting %s",
			       temp2->string.pointer, value_to_write);
	}

	/* Write back the original value */

	write_value.string.length = strlen(temp1->string.pointer);
	write_value.string.pointer = temp1->string.pointer;

	status = acpi_db_write_to_object(node, &write_value);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	/* Ensure that we can read back the original value */

	status = acpi_db_read_from_object(node, ACPI_TYPE_STRING, &temp3);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	if (strcmp(temp1->string.pointer, temp3->string.pointer)) {
		acpi_os_printf(" MISMATCH 3: %s, expecting %s",
			       temp3->string.pointer, temp1->string.pointer);
	}

exit:
	if (temp1) {
		acpi_os_free(temp1);
	}
	if (temp2) {
		acpi_os_free(temp2);
	}
	if (temp3) {
		acpi_os_free(temp3);
	}
	return (status);
}