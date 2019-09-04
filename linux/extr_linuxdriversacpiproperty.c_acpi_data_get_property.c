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
struct TYPE_4__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_3__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ string; TYPE_1__ package; } ;
struct acpi_device_data {union acpi_object* properties; int /*<<< orphan*/  pointer; } ;
typedef  scalar_t__ acpi_object_type ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_ANY ; 
 int EINVAL ; 
 int EPROTO ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_data_get_property(const struct acpi_device_data *data,
				  const char *name, acpi_object_type type,
				  const union acpi_object **obj)
{
	const union acpi_object *properties;
	int i;

	if (!data || !name)
		return -EINVAL;

	if (!data->pointer || !data->properties)
		return -EINVAL;

	properties = data->properties;
	for (i = 0; i < properties->package.count; i++) {
		const union acpi_object *propname, *propvalue;
		const union acpi_object *property;

		property = &properties->package.elements[i];

		propname = &property->package.elements[0];
		propvalue = &property->package.elements[1];

		if (!strcmp(name, propname->string.pointer)) {
			if (type != ACPI_TYPE_ANY && propvalue->type != type)
				return -EPROTO;
			if (obj)
				*obj = propvalue;

			return 0;
		}
	}
	return -EINVAL;
}