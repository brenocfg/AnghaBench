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
struct TYPE_2__ {int bit_length; } ;
union acpi_operand_object {TYPE_1__ common_field; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int) ; 
 int ACPI_INTEGER_BIT_SIZE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static u8
acpi_ex_register_overflow(union acpi_operand_object *obj_desc, u64 value)
{

	if (obj_desc->common_field.bit_length >= ACPI_INTEGER_BIT_SIZE) {
		/*
		 * The field is large enough to hold the maximum integer, so we can
		 * never overflow it.
		 */
		return (FALSE);
	}

	if (value >= ((u64) 1 << obj_desc->common_field.bit_length)) {
		/*
		 * The Value is larger than the maximum value that can fit into
		 * the register.
		 */
		ACPI_ERROR((AE_INFO,
			    "Index value 0x%8.8X%8.8X overflows field width 0x%X",
			    ACPI_FORMAT_UINT64(value),
			    obj_desc->common_field.bit_length));

		return (TRUE);
	}

	/* The Value will fit into the field with no truncation */

	return (FALSE);
}