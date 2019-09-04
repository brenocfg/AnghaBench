#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int resource_type; int /*<<< orphan*/  specific_flags; } ;
union aml_resource {TYPE_4__ address; } ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  type_specific; } ;
struct TYPE_6__ {scalar_t__ resource_type; TYPE_1__ info; } ;
struct TYPE_7__ {TYPE_2__ address; } ;
struct acpi_resource {TYPE_3__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_IO_RANGE ; 
 scalar_t__ ACPI_MEMORY_RANGE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_rs_convert_aml_to_resource (struct acpi_resource*,union aml_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_rs_convert_general_flags ; 
 int /*<<< orphan*/  acpi_rs_convert_io_flags ; 
 int /*<<< orphan*/  acpi_rs_convert_mem_flags ; 

u8
acpi_rs_get_address_common(struct acpi_resource *resource,
			   union aml_resource *aml)
{
	ACPI_FUNCTION_ENTRY();

	/* Validate the Resource Type */

	if ((aml->address.resource_type > 2) &&
	    (aml->address.resource_type < 0xC0)) {
		return (FALSE);
	}

	/* Get the Resource Type and General Flags */

	(void)acpi_rs_convert_aml_to_resource(resource, aml,
					      acpi_rs_convert_general_flags);

	/* Get the Type-Specific Flags (Memory and I/O descriptors only) */

	if (resource->data.address.resource_type == ACPI_MEMORY_RANGE) {
		(void)acpi_rs_convert_aml_to_resource(resource, aml,
						      acpi_rs_convert_mem_flags);
	} else if (resource->data.address.resource_type == ACPI_IO_RANGE) {
		(void)acpi_rs_convert_aml_to_resource(resource, aml,
						      acpi_rs_convert_io_flags);
	} else {
		/* Generic resource type, just grab the type_specific byte */

		resource->data.address.info.type_specific =
		    aml->address.specific_flags;
	}

	return (TRUE);
}