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
struct TYPE_4__ {size_t count; union acpi_object* elements; } ;
struct TYPE_3__ {union acpi_object* pointer; } ;
union acpi_object {int type; TYPE_2__ package; TYPE_1__ buffer; } ;
typedef  size_t u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
#define  ACPI_TYPE_BUFFER 129 
#define  ACPI_TYPE_PACKAGE 128 

void acpi_db_delete_objects(u32 count, union acpi_object *objects)
{
	u32 i;

	for (i = 0; i < count; i++) {
		switch (objects[i].type) {
		case ACPI_TYPE_BUFFER:

			ACPI_FREE(objects[i].buffer.pointer);
			break;

		case ACPI_TYPE_PACKAGE:

			/* Recursive call to delete package elements */

			acpi_db_delete_objects(objects[i].package.count,
					       objects[i].package.elements);

			/* Free the elements array */

			ACPI_FREE(objects[i].package.elements);
			break;

		default:

			break;
		}
	}
}