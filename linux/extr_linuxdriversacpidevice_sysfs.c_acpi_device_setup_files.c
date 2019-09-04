#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_10__ {scalar_t__ power_resources; } ;
struct TYPE_11__ {TYPE_4__ flags; } ;
struct TYPE_9__ {scalar_t__ power_manageable; } ;
struct TYPE_7__ {scalar_t__ bus_address; } ;
struct TYPE_8__ {scalar_t__ unique_id; TYPE_1__ type; int /*<<< orphan*/ * str_obj; int /*<<< orphan*/  ids; } ;
struct acpi_device {int /*<<< orphan*/  data; TYPE_6__ dev; TYPE_5__ power; TYPE_3__ flags; scalar_t__ handle; TYPE_2__ pnp; } ;
struct acpi_buffer {int /*<<< orphan*/ * pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_object (scalar_t__,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_expose_nondev_subnodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_has_method (scalar_t__,char*) ; 
 int /*<<< orphan*/  dev_attr_adr ; 
 int /*<<< orphan*/  dev_attr_description ; 
 int /*<<< orphan*/  dev_attr_eject ; 
 int /*<<< orphan*/  dev_attr_hid ; 
 int /*<<< orphan*/  dev_attr_hrv ; 
 int /*<<< orphan*/  dev_attr_modalias ; 
 int /*<<< orphan*/  dev_attr_path ; 
 int /*<<< orphan*/  dev_attr_power_state ; 
 int /*<<< orphan*/  dev_attr_real_power_state ; 
 int /*<<< orphan*/  dev_attr_status ; 
 int /*<<< orphan*/  dev_attr_sun ; 
 int /*<<< orphan*/  dev_attr_uid ; 
 int device_create_file (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

int acpi_device_setup_files(struct acpi_device *dev)
{
	struct acpi_buffer buffer = {ACPI_ALLOCATE_BUFFER, NULL};
	acpi_status status;
	int result = 0;

	/*
	 * Devices gotten from FADT don't have a "path" attribute
	 */
	if (dev->handle) {
		result = device_create_file(&dev->dev, &dev_attr_path);
		if (result)
			goto end;
	}

	if (!list_empty(&dev->pnp.ids)) {
		result = device_create_file(&dev->dev, &dev_attr_hid);
		if (result)
			goto end;

		result = device_create_file(&dev->dev, &dev_attr_modalias);
		if (result)
			goto end;
	}

	/*
	 * If device has _STR, 'description' file is created
	 */
	if (acpi_has_method(dev->handle, "_STR")) {
		status = acpi_evaluate_object(dev->handle, "_STR",
					NULL, &buffer);
		if (ACPI_FAILURE(status))
			buffer.pointer = NULL;
		dev->pnp.str_obj = buffer.pointer;
		result = device_create_file(&dev->dev, &dev_attr_description);
		if (result)
			goto end;
	}

	if (dev->pnp.type.bus_address)
		result = device_create_file(&dev->dev, &dev_attr_adr);
	if (dev->pnp.unique_id)
		result = device_create_file(&dev->dev, &dev_attr_uid);

	if (acpi_has_method(dev->handle, "_SUN")) {
		result = device_create_file(&dev->dev, &dev_attr_sun);
		if (result)
			goto end;
	}

	if (acpi_has_method(dev->handle, "_HRV")) {
		result = device_create_file(&dev->dev, &dev_attr_hrv);
		if (result)
			goto end;
	}

	if (acpi_has_method(dev->handle, "_STA")) {
		result = device_create_file(&dev->dev, &dev_attr_status);
		if (result)
			goto end;
	}

	/*
	 * If device has _EJ0, 'eject' file is created that is used to trigger
	 * hot-removal function from userland.
	 */
	if (acpi_has_method(dev->handle, "_EJ0")) {
		result = device_create_file(&dev->dev, &dev_attr_eject);
		if (result)
			return result;
	}

	if (dev->flags.power_manageable) {
		result = device_create_file(&dev->dev, &dev_attr_power_state);
		if (result)
			return result;

		if (dev->power.flags.power_resources)
			result = device_create_file(&dev->dev,
						    &dev_attr_real_power_state);
	}

	acpi_expose_nondev_subnodes(&dev->dev.kobj, &dev->data);

end:
	return result;
}