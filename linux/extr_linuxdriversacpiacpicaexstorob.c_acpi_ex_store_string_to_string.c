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
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  pointer; } ;
struct TYPE_3__ {int flags; } ;
union acpi_operand_object {TYPE_2__ string; TYPE_1__ common; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_CAST_PTR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_STATIC_POINTER ; 
 int buffer ; 
 int /*<<< orphan*/  ex_store_string_to_string ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int u8 ; 

acpi_status
acpi_ex_store_string_to_string(union acpi_operand_object *source_desc,
			       union acpi_operand_object *target_desc)
{
	u32 length;
	u8 *buffer;

	ACPI_FUNCTION_TRACE_PTR(ex_store_string_to_string, source_desc);

	/* If Source and Target are the same, just return */

	if (source_desc == target_desc) {
		return_ACPI_STATUS(AE_OK);
	}

	/* We know that source_desc is a string by now */

	buffer = ACPI_CAST_PTR(u8, source_desc->string.pointer);
	length = source_desc->string.length;

	/*
	 * Replace existing string value if it will fit and the string
	 * pointer is not a static pointer (part of an ACPI table)
	 */
	if ((length < target_desc->string.length) &&
	    (!(target_desc->common.flags & AOPOBJ_STATIC_POINTER))) {
		/*
		 * String will fit in existing non-static buffer.
		 * Clear old string and copy in the new one
		 */
		memset(target_desc->string.pointer, 0,
		       (acpi_size)target_desc->string.length + 1);
		memcpy(target_desc->string.pointer, buffer, length);
	} else {
		/*
		 * Free the current buffer, then allocate a new buffer
		 * large enough to hold the value
		 */
		if (target_desc->string.pointer &&
		    (!(target_desc->common.flags & AOPOBJ_STATIC_POINTER))) {

			/* Only free if not a pointer into the DSDT */

			ACPI_FREE(target_desc->string.pointer);
		}

		target_desc->string.pointer =
		    ACPI_ALLOCATE_ZEROED((acpi_size)length + 1);

		if (!target_desc->string.pointer) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		target_desc->common.flags &= ~AOPOBJ_STATIC_POINTER;
		memcpy(target_desc->string.pointer, buffer, length);
	}

	/* Set the new target length */

	target_desc->string.length = length;
	return_ACPI_STATUS(AE_OK);
}