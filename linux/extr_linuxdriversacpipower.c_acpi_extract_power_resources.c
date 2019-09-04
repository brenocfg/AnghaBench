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
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {unsigned int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_1__ reference; TYPE_2__ package; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 int ENODATA ; 
 int ENODEV ; 
 int acpi_add_power_resource (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_power_resource_is_dup (union acpi_object*,unsigned int,unsigned int) ; 
 int acpi_power_resources_list_add (int /*<<< orphan*/ ,struct list_head*) ; 
 int /*<<< orphan*/  acpi_power_resources_list_free (struct list_head*) ; 

int acpi_extract_power_resources(union acpi_object *package, unsigned int start,
				 struct list_head *list)
{
	unsigned int i;
	int err = 0;

	for (i = start; i < package->package.count; i++) {
		union acpi_object *element = &package->package.elements[i];
		acpi_handle rhandle;

		if (element->type != ACPI_TYPE_LOCAL_REFERENCE) {
			err = -ENODATA;
			break;
		}
		rhandle = element->reference.handle;
		if (!rhandle) {
			err = -ENODEV;
			break;
		}

		/* Some ACPI tables contain duplicate power resource references */
		if (acpi_power_resource_is_dup(package, start, i))
			continue;

		err = acpi_add_power_resource(rhandle);
		if (err)
			break;

		err = acpi_power_resources_list_add(rhandle, list);
		if (err)
			break;
	}
	if (err)
		acpi_power_resources_list_free(list);

	return err;
}