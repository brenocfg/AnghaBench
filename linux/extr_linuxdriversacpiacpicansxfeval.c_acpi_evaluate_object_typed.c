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
union acpi_object {scalar_t__ type; } ;
typedef  scalar_t__ u8 ;
struct acpi_object_list {int dummy; } ;
struct acpi_buffer {scalar_t__ length; int /*<<< orphan*/ * pointer; } ;
typedef  scalar_t__ acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_object_type ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,scalar_t__,struct acpi_object_list*,struct acpi_buffer*,scalar_t__)) ; 
 scalar_t__ ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_NULL_OBJECT ; 
 int /*<<< orphan*/  AE_TYPE ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 char* acpi_ns_get_external_pathname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_evaluate_object_typed(acpi_handle handle,
			   acpi_string pathname,
			   struct acpi_object_list *external_params,
			   struct acpi_buffer *return_buffer,
			   acpi_object_type return_type)
{
	acpi_status status;
	u8 free_buffer_on_error = FALSE;
	acpi_handle target_handle;
	char *full_pathname;

	ACPI_FUNCTION_TRACE(acpi_evaluate_object_typed);

	/* Return buffer must be valid */

	if (!return_buffer) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	if (return_buffer->length == ACPI_ALLOCATE_BUFFER) {
		free_buffer_on_error = TRUE;
	}

	/* Get a handle here, in order to build an error message if needed */

	target_handle = handle;
	if (pathname) {
		status = acpi_get_handle(handle, pathname, &target_handle);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}
	}

	full_pathname = acpi_ns_get_external_pathname(target_handle);
	if (!full_pathname) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Evaluate the object */

	status = acpi_evaluate_object(target_handle, NULL, external_params,
				      return_buffer);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	/* Type ANY means "don't care about return value type" */

	if (return_type == ACPI_TYPE_ANY) {
		goto exit;
	}

	if (return_buffer->length == 0) {

		/* Error because caller specifically asked for a return value */

		ACPI_ERROR((AE_INFO, "%s did not return any object",
			    full_pathname));
		status = AE_NULL_OBJECT;
		goto exit;
	}

	/* Examine the object type returned from evaluate_object */

	if (((union acpi_object *)return_buffer->pointer)->type == return_type) {
		goto exit;
	}

	/* Return object type does not match requested type */

	ACPI_ERROR((AE_INFO,
		    "Incorrect return type from %s - received [%s], requested [%s]",
		    full_pathname,
		    acpi_ut_get_type_name(((union acpi_object *)return_buffer->
					   pointer)->type),
		    acpi_ut_get_type_name(return_type)));

	if (free_buffer_on_error) {
		/*
		 * Free a buffer created via ACPI_ALLOCATE_BUFFER.
		 * Note: We use acpi_os_free here because acpi_os_allocate was used
		 * to allocate the buffer. This purposefully bypasses the
		 * (optionally enabled) allocation tracking mechanism since we
		 * only want to track internal allocations.
		 */
		acpi_os_free(return_buffer->pointer);
		return_buffer->pointer = NULL;
	}

	return_buffer->length = 0;
	status = AE_TYPE;

exit:
	ACPI_FREE(full_pathname);
	return_ACPI_STATUS(status);
}