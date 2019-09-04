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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_info {int /*<<< orphan*/  count; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  char* acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_LOCAL_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (scalar_t__) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ns_dump_one_object (char*,int /*<<< orphan*/ ,struct acpi_walk_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ns_handle_to_pathname (char*,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,char*) ; 

__attribute__((used)) static acpi_status
acpi_db_walk_for_specific_objects(acpi_handle obj_handle,
				  u32 nesting_level,
				  void *context, void **return_value)
{
	struct acpi_walk_info *info = (struct acpi_walk_info *)context;
	struct acpi_buffer buffer;
	acpi_status status;

	info->count++;

	/* Get and display the full pathname to this object */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_ns_handle_to_pathname(obj_handle, &buffer, TRUE);
	if (ACPI_FAILURE(status)) {
		acpi_os_printf("Could Not get pathname for object %p\n",
			       obj_handle);
		return (AE_OK);
	}

	acpi_os_printf("%32s", (char *)buffer.pointer);
	ACPI_FREE(buffer.pointer);

	/* Dump short info about the object */

	(void)acpi_ns_dump_one_object(obj_handle, nesting_level, info, NULL);
	return (AE_OK);
}