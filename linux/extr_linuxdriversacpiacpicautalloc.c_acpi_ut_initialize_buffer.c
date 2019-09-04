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
struct acpi_buffer {int length; int /*<<< orphan*/  pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE (int) ; 
#define  ACPI_ALLOCATE_BUFFER 130 
#define  ACPI_ALLOCATE_LOCAL_BUFFER 129 
#define  ACPI_NO_BUFFER 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_os_allocate (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

acpi_status
acpi_ut_initialize_buffer(struct acpi_buffer *buffer, acpi_size required_length)
{
	acpi_size input_buffer_length;

	/* Parameter validation */

	if (!buffer || !required_length) {
		return (AE_BAD_PARAMETER);
	}

	/*
	 * Buffer->Length is used as both an input and output parameter. Get the
	 * input actual length and set the output required buffer length.
	 */
	input_buffer_length = buffer->length;
	buffer->length = required_length;

	/*
	 * The input buffer length contains the actual buffer length, or the type
	 * of buffer to be allocated by this routine.
	 */
	switch (input_buffer_length) {
	case ACPI_NO_BUFFER:

		/* Return the exception (and the required buffer length) */

		return (AE_BUFFER_OVERFLOW);

	case ACPI_ALLOCATE_BUFFER:
		/*
		 * Allocate a new buffer. We directectly call acpi_os_allocate here to
		 * purposefully bypass the (optionally enabled) internal allocation
		 * tracking mechanism since we only want to track internal
		 * allocations. Note: The caller should use acpi_os_free to free this
		 * buffer created via ACPI_ALLOCATE_BUFFER.
		 */
		buffer->pointer = acpi_os_allocate(required_length);
		break;

	case ACPI_ALLOCATE_LOCAL_BUFFER:

		/* Allocate a new buffer with local interface to allow tracking */

		buffer->pointer = ACPI_ALLOCATE(required_length);
		break;

	default:

		/* Existing buffer: Validate the size of the buffer */

		if (input_buffer_length < required_length) {
			return (AE_BUFFER_OVERFLOW);
		}
		break;
	}

	/* Validate allocation from above or input buffer pointer */

	if (!buffer->pointer) {
		return (AE_NO_MEMORY);
	}

	/* Have a valid buffer, clear it */

	memset(buffer->pointer, 0, required_length);
	return (AE_OK);
}