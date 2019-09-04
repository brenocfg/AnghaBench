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
struct TYPE_2__ {int /*<<< orphan*/  gpe_block; } ;
union acpi_operand_object {TYPE_1__ device; } ;
typedef  size_t u32 ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_gpe_event_info {int dummy; } ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 size_t ACPI_MAX_GPE_BLOCKS ; 
 struct acpi_gpe_event_info* acpi_ev_low_get_gpe_info (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * acpi_gbl_gpe_fadt_blocks ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 

struct acpi_gpe_event_info *acpi_ev_get_gpe_event_info(acpi_handle gpe_device,
						       u32 gpe_number)
{
	union acpi_operand_object *obj_desc;
	struct acpi_gpe_event_info *gpe_info;
	u32 i;

	ACPI_FUNCTION_ENTRY();

	/* A NULL gpe_device means use the FADT-defined GPE block(s) */

	if (!gpe_device) {

		/* Examine GPE Block 0 and 1 (These blocks are permanent) */

		for (i = 0; i < ACPI_MAX_GPE_BLOCKS; i++) {
			gpe_info = acpi_ev_low_get_gpe_info(gpe_number,
							    acpi_gbl_gpe_fadt_blocks
							    [i]);
			if (gpe_info) {
				return (gpe_info);
			}
		}

		/* The gpe_number was not in the range of either FADT GPE block */

		return (NULL);
	}

	/* A Non-NULL gpe_device means this is a GPE Block Device */

	obj_desc =
	    acpi_ns_get_attached_object((struct acpi_namespace_node *)
					       gpe_device);
	if (!obj_desc || !obj_desc->device.gpe_block) {
		return (NULL);
	}

	return (acpi_ev_low_get_gpe_info
		(gpe_number, obj_desc->device.gpe_block));
}