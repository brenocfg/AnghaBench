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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct acpi_resource {int dummy; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 void* ACPI_ALLOCATE_ZEROED (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FREE (void*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (scalar_t__ (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_resource**)) ; 
 scalar_t__ AE_AML_NO_RESOURCE_END_TAG ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  acpi_rs_convert_aml_to_resources ; 
 scalar_t__ acpi_rs_get_list_length (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_ut_walk_aml_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status
acpi_buffer_to_resource(u8 *aml_buffer,
			u16 aml_buffer_length,
			struct acpi_resource **resource_ptr)
{
	acpi_status status;
	acpi_size list_size_needed;
	void *resource;
	void *current_resource_ptr;

	ACPI_FUNCTION_TRACE(acpi_buffer_to_resource);

	/*
	 * Note: we allow AE_AML_NO_RESOURCE_END_TAG, since an end tag
	 * is not required here.
	 */

	/* Get the required length for the converted resource */

	status =
	    acpi_rs_get_list_length(aml_buffer, aml_buffer_length,
				    &list_size_needed);
	if (status == AE_AML_NO_RESOURCE_END_TAG) {
		status = AE_OK;
	}
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Allocate a buffer for the converted resource */

	resource = ACPI_ALLOCATE_ZEROED(list_size_needed);
	current_resource_ptr = resource;
	if (!resource) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Perform the AML-to-Resource conversion */

	status = acpi_ut_walk_aml_resources(NULL, aml_buffer, aml_buffer_length,
					    acpi_rs_convert_aml_to_resources,
					    &current_resource_ptr);
	if (status == AE_AML_NO_RESOURCE_END_TAG) {
		status = AE_OK;
	}
	if (ACPI_FAILURE(status)) {
		ACPI_FREE(resource);
	} else {
		*resource_ptr = resource;
	}

	return_ACPI_STATUS(status);
}