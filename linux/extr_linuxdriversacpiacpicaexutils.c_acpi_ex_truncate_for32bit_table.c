#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_2__ integer; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int acpi_gbl_integer_byte_width ; 

u8 acpi_ex_truncate_for32bit_table(union acpi_operand_object *obj_desc)
{

	ACPI_FUNCTION_ENTRY();

	/*
	 * Object must be a valid number and we must be executing
	 * a control method. Object could be NS node for AML_INT_NAMEPATH_OP.
	 */
	if ((!obj_desc) ||
	    (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) != ACPI_DESC_TYPE_OPERAND) ||
	    (obj_desc->common.type != ACPI_TYPE_INTEGER)) {
		return (FALSE);
	}

	if ((acpi_gbl_integer_byte_width == 4) &&
	    (obj_desc->integer.value > (u64)ACPI_UINT32_MAX)) {
		/*
		 * We are executing in a 32-bit ACPI table. Truncate
		 * the value to 32 bits by zeroing out the upper 32-bit field
		 */
		obj_desc->integer.value &= (u64)ACPI_UINT32_MAX;
		return (TRUE);
	}

	return (FALSE);
}