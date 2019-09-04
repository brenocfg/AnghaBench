#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union acpi_object {int dummy; } acpi_object ;
struct TYPE_5__ {int of_compatible_ok; } ;
struct TYPE_8__ {union acpi_object const* of_compatible; } ;
struct acpi_device {TYPE_1__ flags; TYPE_4__ data; TYPE_3__* parent; } ;
struct TYPE_6__ {scalar_t__ of_compatible_ok; } ;
struct TYPE_7__ {TYPE_2__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int acpi_data_get_property_array (TYPE_4__*,char*,int /*<<< orphan*/ ,union acpi_object const**) ; 
 int acpi_dev_get_property (struct acpi_device*,char*,int /*<<< orphan*/ ,union acpi_object const**) ; 

__attribute__((used)) static void acpi_init_of_compatible(struct acpi_device *adev)
{
	const union acpi_object *of_compatible;
	int ret;

	ret = acpi_data_get_property_array(&adev->data, "compatible",
					   ACPI_TYPE_STRING, &of_compatible);
	if (ret) {
		ret = acpi_dev_get_property(adev, "compatible",
					    ACPI_TYPE_STRING, &of_compatible);
		if (ret) {
			if (adev->parent
			    && adev->parent->flags.of_compatible_ok)
				goto out;

			return;
		}
	}
	adev->data.of_compatible = of_compatible;

 out:
	adev->flags.of_compatible_ok = 1;
}