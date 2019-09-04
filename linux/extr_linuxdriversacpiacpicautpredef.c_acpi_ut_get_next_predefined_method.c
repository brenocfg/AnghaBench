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
struct TYPE_2__ {int expected_btypes; } ;
union acpi_predefined_info {TYPE_1__ info; } ;

/* Variables and functions */
 int ACPI_RTYPE_ALL ; 
 int ACPI_RTYPE_PACKAGE ; 

const union acpi_predefined_info *acpi_ut_get_next_predefined_method(const union
								     acpi_predefined_info
								     *this_name)
{

	/*
	 * Skip next entry in the table if this name returns a Package
	 * (next entry contains the package info)
	 */
	if ((this_name->info.expected_btypes & ACPI_RTYPE_PACKAGE) &&
	    (this_name->info.expected_btypes != ACPI_RTYPE_ALL)) {
		this_name++;
	}

	this_name++;
	return (this_name);
}