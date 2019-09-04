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
struct TYPE_2__ {int /*<<< orphan*/  address; int /*<<< orphan*/  length; } ;
union acpi_operand_object {TYPE_1__ region; } ;
typedef  scalar_t__ u32 ;
struct acpi_mem_space_context {int /*<<< orphan*/  address; int /*<<< orphan*/  length; scalar_t__ mapped_length; int /*<<< orphan*/  mapped_logical_address; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 struct acpi_mem_space_context* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_mem_space_context*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_REGION_DEACTIVATE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_os_unmap_memory (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ev_system_memory_region_setup ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_system_memory_region_setup(acpi_handle handle,
				   u32 function,
				   void *handler_context, void **region_context)
{
	union acpi_operand_object *region_desc =
	    (union acpi_operand_object *)handle;
	struct acpi_mem_space_context *local_region_context;

	ACPI_FUNCTION_TRACE(ev_system_memory_region_setup);

	if (function == ACPI_REGION_DEACTIVATE) {
		if (*region_context) {
			local_region_context =
			    (struct acpi_mem_space_context *)*region_context;

			/* Delete a cached mapping if present */

			if (local_region_context->mapped_length) {
				acpi_os_unmap_memory(local_region_context->
						     mapped_logical_address,
						     local_region_context->
						     mapped_length);
			}
			ACPI_FREE(local_region_context);
			*region_context = NULL;
		}
		return_ACPI_STATUS(AE_OK);
	}

	/* Create a new context */

	local_region_context =
	    ACPI_ALLOCATE_ZEROED(sizeof(struct acpi_mem_space_context));
	if (!(local_region_context)) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Save the region length and address for use in the handler */

	local_region_context->length = region_desc->region.length;
	local_region_context->address = region_desc->region.address;

	*region_context = local_region_context;
	return_ACPI_STATUS(AE_OK);
}