#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct topstar_laptop {struct acpi_device* device; } ;
struct acpi_device {struct topstar_laptop* driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* TOPSTAR_LAPTOP_CLASS ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct topstar_laptop*) ; 
 struct topstar_laptop* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ led_workaround ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  topstar_acpi_exit (struct topstar_laptop*) ; 
 int topstar_acpi_init (struct topstar_laptop*) ; 
 int /*<<< orphan*/  topstar_dmi_ids ; 
 int /*<<< orphan*/  topstar_input_exit (struct topstar_laptop*) ; 
 int topstar_input_init (struct topstar_laptop*) ; 
 int topstar_led_init (struct topstar_laptop*) ; 
 int /*<<< orphan*/  topstar_platform_exit (struct topstar_laptop*) ; 
 int topstar_platform_init (struct topstar_laptop*) ; 

__attribute__((used)) static int topstar_acpi_add(struct acpi_device *device)
{
	struct topstar_laptop *topstar;
	int err;

	dmi_check_system(topstar_dmi_ids);

	topstar = kzalloc(sizeof(struct topstar_laptop), GFP_KERNEL);
	if (!topstar)
		return -ENOMEM;

	strcpy(acpi_device_name(device), "Topstar TPSACPI");
	strcpy(acpi_device_class(device), TOPSTAR_LAPTOP_CLASS);
	device->driver_data = topstar;
	topstar->device = device;

	err = topstar_acpi_init(topstar);
	if (err)
		goto err_free;

	err = topstar_platform_init(topstar);
	if (err)
		goto err_acpi_exit;

	err = topstar_input_init(topstar);
	if (err)
		goto err_platform_exit;

	if (led_workaround) {
		err = topstar_led_init(topstar);
		if (err)
			goto err_input_exit;
	}

	return 0;

err_input_exit:
	topstar_input_exit(topstar);
err_platform_exit:
	topstar_platform_exit(topstar);
err_acpi_exit:
	topstar_acpi_exit(topstar);
err_free:
	kfree(topstar);
	return err;
}