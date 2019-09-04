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
typedef  int u32 ;
typedef  size_t acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int ACPI_NS_NEWSCOPE ; 
 int ACPI_NS_NORMAL ; 
 size_t ACPI_TYPE_LOCAL_MAX ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__* acpi_gbl_ns_properties ; 

u32 acpi_ns_opens_scope(acpi_object_type type)
{
	ACPI_FUNCTION_ENTRY();

	if (type > ACPI_TYPE_LOCAL_MAX) {

		/* type code out of range  */

		ACPI_WARNING((AE_INFO, "Invalid Object Type 0x%X", type));
		return (ACPI_NS_NORMAL);
	}

	return (((u32)acpi_gbl_ns_properties[type]) & ACPI_NS_NEWSCOPE);
}