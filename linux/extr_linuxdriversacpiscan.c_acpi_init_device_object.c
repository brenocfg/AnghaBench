#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int match_driver; int initialized; int /*<<< orphan*/  enumeration_by_parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  ids; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;
struct acpi_device {int device_type; int dep_unmet; int /*<<< orphan*/  dev; TYPE_2__ flags; TYPE_3__ pnp; TYPE_1__ fwnode; int /*<<< orphan*/  parent; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_bus_get_flags (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_bus_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_clear_enumerated (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_enumeration_by_parent (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_fwnode_ops ; 
 int /*<<< orphan*/  acpi_device_get_busid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_init_coherency (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_init_properties (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_set_device_status (struct acpi_device*,unsigned long long) ; 
 int /*<<< orphan*/  acpi_set_pnp_ids (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_initialize (int /*<<< orphan*/ *) ; 

void acpi_init_device_object(struct acpi_device *device, acpi_handle handle,
			     int type, unsigned long long sta)
{
	INIT_LIST_HEAD(&device->pnp.ids);
	device->device_type = type;
	device->handle = handle;
	device->parent = acpi_bus_get_parent(handle);
	device->fwnode.ops = &acpi_device_fwnode_ops;
	acpi_set_device_status(device, sta);
	acpi_device_get_busid(device);
	acpi_set_pnp_ids(handle, &device->pnp, type);
	acpi_init_properties(device);
	acpi_bus_get_flags(device);
	device->flags.match_driver = false;
	device->flags.initialized = true;
	device->flags.enumeration_by_parent =
		acpi_device_enumeration_by_parent(device);
	acpi_device_clear_enumerated(device);
	device_initialize(&device->dev);
	dev_set_uevent_suppress(&device->dev, true);
	acpi_init_coherency(device);
	/* Assume there are unmet deps until acpi_device_dep_initialize() runs */
	device->dep_unmet = 1;
}