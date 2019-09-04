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
struct TYPE_2__ {int type; } ;
union acpi_operand_object {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_RTYPE_ANY ; 
 int /*<<< orphan*/  ACPI_RTYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_RTYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_RTYPE_NONE ; 
 int /*<<< orphan*/  ACPI_RTYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_RTYPE_REFERENCE ; 
 int /*<<< orphan*/  ACPI_RTYPE_STRING ; 
#define  ACPI_TYPE_BUFFER 132 
#define  ACPI_TYPE_INTEGER 131 
#define  ACPI_TYPE_LOCAL_REFERENCE 130 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 

__attribute__((used)) static u32 acpi_ns_get_bitmapped_type(union acpi_operand_object *return_object)
{
	u32 return_btype;

	if (!return_object) {
		return (ACPI_RTYPE_NONE);
	}

	/* Map acpi_object_type to internal bitmapped type */

	switch (return_object->common.type) {
	case ACPI_TYPE_INTEGER:

		return_btype = ACPI_RTYPE_INTEGER;
		break;

	case ACPI_TYPE_BUFFER:

		return_btype = ACPI_RTYPE_BUFFER;
		break;

	case ACPI_TYPE_STRING:

		return_btype = ACPI_RTYPE_STRING;
		break;

	case ACPI_TYPE_PACKAGE:

		return_btype = ACPI_RTYPE_PACKAGE;
		break;

	case ACPI_TYPE_LOCAL_REFERENCE:

		return_btype = ACPI_RTYPE_REFERENCE;
		break;

	default:

		/* Not one of the supported objects, must be incorrect */

		return_btype = ACPI_RTYPE_ANY;
		break;
	}

	return (return_btype);
}