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
struct acpi_power_meter_resource {int num_sensors; TYPE_3__* sensors; TYPE_2__* acpi_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_1__ attr; } ;
struct TYPE_7__ {TYPE_4__ dev_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  remove_domain_devices (struct acpi_power_meter_resource*) ; 

__attribute__((used)) static void remove_attrs(struct acpi_power_meter_resource *resource)
{
	int i;

	for (i = 0; i < resource->num_sensors; i++) {
		if (!resource->sensors[i].dev_attr.attr.name)
			continue;
		device_remove_file(&resource->acpi_dev->dev,
				   &resource->sensors[i].dev_attr);
	}

	remove_domain_devices(resource);

	resource->num_sensors = 0;
}