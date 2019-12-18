#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fujitsu_laptop {TYPE_2__* input; int /*<<< orphan*/  phys; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_6__ {TYPE_1__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 char* acpi_device_hid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 struct fujitsu_laptop* acpi_driver_data (struct acpi_device*) ; 
 TYPE_2__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fujitsu_laptop_dmi_table ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  keymap ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int sparse_keymap_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_fujitsu_laptop_input_setup(struct acpi_device *device)
{
	struct fujitsu_laptop *priv = acpi_driver_data(device);
	int ret;

	priv->input = devm_input_allocate_device(&device->dev);
	if (!priv->input)
		return -ENOMEM;

	snprintf(priv->phys, sizeof(priv->phys), "%s/input0",
		 acpi_device_hid(device));

	priv->input->name = acpi_device_name(device);
	priv->input->phys = priv->phys;
	priv->input->id.bustype = BUS_HOST;

	dmi_check_system(fujitsu_laptop_dmi_table);
	ret = sparse_keymap_setup(priv->input, keymap, NULL);
	if (ret)
		return ret;

	return input_register_device(priv->input);
}