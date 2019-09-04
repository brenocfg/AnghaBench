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
struct TYPE_2__ {scalar_t__ length; int /*<<< orphan*/  pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_buffer {union acpi_object* pointer; void* length; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_rsdesc_size ;

/* Variables and functions */
 void* ACPI_ALLOCATE_LOCAL_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  acpi_dm_compare_aml_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union acpi_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_object (struct acpi_namespace_node*,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_current_resources (struct acpi_namespace_node*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 int /*<<< orphan*/  acpi_rs_create_aml_resources (struct acpi_buffer*,struct acpi_buffer*) ; 

__attribute__((used)) static acpi_status
acpi_dm_test_resource_conversion(struct acpi_namespace_node *node, char *name)
{
	acpi_status status;
	struct acpi_buffer return_buffer;
	struct acpi_buffer resource_buffer;
	struct acpi_buffer new_aml;
	union acpi_object *original_aml;

	acpi_os_printf("Resource Conversion Comparison:\n");

	new_aml.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	return_buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	resource_buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;

	/* Get the original _CRS AML resource template */

	status = acpi_evaluate_object(node, name, NULL, &return_buffer);
	if (ACPI_FAILURE(status)) {
		acpi_os_printf("Could not obtain %s: %s\n",
			       name, acpi_format_exception(status));
		return (status);
	}

	/* Get the AML resource template, converted to internal resource structs */

	status = acpi_get_current_resources(node, &resource_buffer);
	if (ACPI_FAILURE(status)) {
		acpi_os_printf("AcpiGetCurrentResources failed: %s\n",
			       acpi_format_exception(status));
		goto exit1;
	}

	/* Convert internal resource list to external AML resource template */

	status = acpi_rs_create_aml_resources(&resource_buffer, &new_aml);
	if (ACPI_FAILURE(status)) {
		acpi_os_printf("AcpiRsCreateAmlResources failed: %s\n",
			       acpi_format_exception(status));
		goto exit2;
	}

	/* Compare original AML to the newly created AML resource list */

	original_aml = return_buffer.pointer;

	acpi_dm_compare_aml_resources(original_aml->buffer.pointer,
				      (acpi_rsdesc_size)original_aml->buffer.
				      length, new_aml.pointer,
				      (acpi_rsdesc_size)new_aml.length);

	/* Cleanup and exit */

	ACPI_FREE(new_aml.pointer);
exit2:
	ACPI_FREE(resource_buffer.pointer);
exit1:
	ACPI_FREE(return_buffer.pointer);
	return (status);
}