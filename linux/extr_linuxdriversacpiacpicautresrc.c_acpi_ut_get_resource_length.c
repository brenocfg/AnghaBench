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
typedef  scalar_t__ u16 ;
typedef  scalar_t__ acpi_rs_length ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADD_PTR (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int ACPI_GET8 (void*) ; 
 int /*<<< orphan*/  ACPI_MOVE_16_TO_16 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int ACPI_RESOURCE_NAME_LARGE ; 
 int ACPI_RESOURCE_NAME_SMALL_LENGTH_MASK ; 
 int /*<<< orphan*/  u8 ; 

u16 acpi_ut_get_resource_length(void *aml)
{
	acpi_rs_length resource_length;

	ACPI_FUNCTION_ENTRY();

	/*
	 * Byte 0 contains the descriptor name (Resource Type)
	 * Examine the large/small bit in the resource header
	 */
	if (ACPI_GET8(aml) & ACPI_RESOURCE_NAME_LARGE) {

		/* Large Resource type -- bytes 1-2 contain the 16-bit length */

		ACPI_MOVE_16_TO_16(&resource_length, ACPI_ADD_PTR(u8, aml, 1));

	} else {
		/* Small Resource type -- bits 2:0 of byte 0 contain the length */

		resource_length = (u16) (ACPI_GET8(aml) &
					 ACPI_RESOURCE_NAME_SMALL_LENGTH_MASK);
	}

	return (resource_length);
}