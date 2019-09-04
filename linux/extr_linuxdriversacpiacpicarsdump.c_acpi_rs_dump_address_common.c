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
struct TYPE_2__ {int resource_type; } ;
union acpi_resource_data {TYPE_1__ address; } ;
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
#define  ACPI_BUS_NUMBER_RANGE 130 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
#define  ACPI_IO_RANGE 129 
#define  ACPI_MEMORY_RANGE 128 
 int /*<<< orphan*/  acpi_rs_dump_descriptor (union acpi_resource_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_rs_dump_general_flags ; 
 int /*<<< orphan*/  acpi_rs_dump_io_flags ; 
 int /*<<< orphan*/  acpi_rs_dump_memory_flags ; 
 int /*<<< orphan*/  acpi_rs_out_integer8 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_rs_out_string (char*,char*) ; 

__attribute__((used)) static void acpi_rs_dump_address_common(union acpi_resource_data *resource)
{
	ACPI_FUNCTION_ENTRY();

	/* Decode the type-specific flags */

	switch (resource->address.resource_type) {
	case ACPI_MEMORY_RANGE:

		acpi_rs_dump_descriptor(resource, acpi_rs_dump_memory_flags);
		break;

	case ACPI_IO_RANGE:

		acpi_rs_dump_descriptor(resource, acpi_rs_dump_io_flags);
		break;

	case ACPI_BUS_NUMBER_RANGE:

		acpi_rs_out_string("Resource Type", "Bus Number Range");
		break;

	default:

		acpi_rs_out_integer8("Resource Type",
				     (u8) resource->address.resource_type);
		break;
	}

	/* Decode the general flags */

	acpi_rs_dump_descriptor(resource, acpi_rs_dump_general_flags);
}