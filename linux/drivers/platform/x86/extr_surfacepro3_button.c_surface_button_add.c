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
struct surface_button {int /*<<< orphan*/  phys; struct input_dev* input; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; } ;
struct acpi_device {int /*<<< orphan*/  dev; struct surface_button* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KEY_LEFTMETA ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  KEY_VOLUMEDOWN ; 
 int /*<<< orphan*/  KEY_VOLUMEUP ; 
 int /*<<< orphan*/  SURFACE_BUTTON_DEVICE_NAME ; 
 int /*<<< orphan*/  SURFACE_BUTTON_OBJ_NAME ; 
 int /*<<< orphan*/  acpi_device_bid (struct acpi_device*) ; 
 char* acpi_device_hid (struct acpi_device*) ; 
 char* acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct surface_button*) ; 
 struct surface_button* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  surface_button_check_MSHW0040 (struct acpi_device*) ; 

__attribute__((used)) static int surface_button_add(struct acpi_device *device)
{
	struct surface_button *button;
	struct input_dev *input;
	const char *hid = acpi_device_hid(device);
	char *name;
	int error;

	if (strncmp(acpi_device_bid(device), SURFACE_BUTTON_OBJ_NAME,
	    strlen(SURFACE_BUTTON_OBJ_NAME)))
		return -ENODEV;

	if (!surface_button_check_MSHW0040(device))
		return -ENODEV;

	button = kzalloc(sizeof(struct surface_button), GFP_KERNEL);
	if (!button)
		return -ENOMEM;

	device->driver_data = button;
	button->input = input = input_allocate_device();
	if (!input) {
		error = -ENOMEM;
		goto err_free_button;
	}

	name = acpi_device_name(device);
	strcpy(name, SURFACE_BUTTON_DEVICE_NAME);
	snprintf(button->phys, sizeof(button->phys), "%s/buttons", hid);

	input->name = name;
	input->phys = button->phys;
	input->id.bustype = BUS_HOST;
	input->dev.parent = &device->dev;
	input_set_capability(input, EV_KEY, KEY_POWER);
	input_set_capability(input, EV_KEY, KEY_LEFTMETA);
	input_set_capability(input, EV_KEY, KEY_VOLUMEUP);
	input_set_capability(input, EV_KEY, KEY_VOLUMEDOWN);

	error = input_register_device(input);
	if (error)
		goto err_free_input;

	device_init_wakeup(&device->dev, true);
	dev_info(&device->dev,
			"%s [%s]\n", name, acpi_device_bid(device));
	return 0;

 err_free_input:
	input_free_device(input);
 err_free_button:
	kfree(button);
	return error;
}