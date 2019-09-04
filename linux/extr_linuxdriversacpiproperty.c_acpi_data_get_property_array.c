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
struct TYPE_4__ {int count; TYPE_1__* elements; } ;
union acpi_object {TYPE_2__ package; } ;
struct acpi_device_data {int dummy; } ;
typedef  scalar_t__ acpi_object_type ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int EPROTO ; 
 int acpi_data_get_property (struct acpi_device_data const*,char const*,int /*<<< orphan*/ ,union acpi_object const**) ; 

__attribute__((used)) static int acpi_data_get_property_array(const struct acpi_device_data *data,
					const char *name,
					acpi_object_type type,
					const union acpi_object **obj)
{
	const union acpi_object *prop;
	int ret, i;

	ret = acpi_data_get_property(data, name, ACPI_TYPE_PACKAGE, &prop);
	if (ret)
		return ret;

	if (type != ACPI_TYPE_ANY) {
		/* Check that all elements are of correct type. */
		for (i = 0; i < prop->package.count; i++)
			if (prop->package.elements[i].type != type)
				return -EPROTO;
	}
	if (obj)
		*obj = prop;

	return 0;
}