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
typedef  size_t acpi_object_type ;

/* Variables and functions */
 size_t ACPI_TYPE_INVALID ; 
 char const* acpi_gbl_bad_type ; 
 char const** acpi_gbl_ns_type_names ; 

const char *acpi_ut_get_type_name(acpi_object_type type)
{

	if (type > ACPI_TYPE_INVALID) {
		return (acpi_gbl_bad_type);
	}

	return (acpi_gbl_ns_type_names[type]);
}