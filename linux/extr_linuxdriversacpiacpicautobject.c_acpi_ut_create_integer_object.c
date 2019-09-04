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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
union acpi_operand_object {TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_PTR (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ut_create_integer_object ; 

union acpi_operand_object *acpi_ut_create_integer_object(u64 initial_value)
{
	union acpi_operand_object *integer_desc;

	ACPI_FUNCTION_TRACE(ut_create_integer_object);

	/* Create and initialize a new integer object */

	integer_desc = acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
	if (!integer_desc) {
		return_PTR(NULL);
	}

	integer_desc->integer.value = initial_value;
	return_PTR(integer_desc);
}