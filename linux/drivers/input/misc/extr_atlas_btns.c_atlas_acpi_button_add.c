#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_8__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_9__ {char* name; char* phys; int keycodesize; int keycodemax; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; scalar_t__* keycode; TYPE_1__ id; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 scalar_t__ KEY_F1 ; 
 scalar_t__ KEY_RESERVED ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_atlas_button_handler ; 
 int /*<<< orphan*/  acpi_atlas_button_setup ; 
 int /*<<< orphan*/  acpi_install_address_space_handler (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct acpi_device*) ; 
 scalar_t__* atlas_keymap ; 
 TYPE_2__* input_allocate_device () ; 
 TYPE_2__* input_dev ; 
 int /*<<< orphan*/  input_free_device (TYPE_2__*) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int atlas_acpi_button_add(struct acpi_device *device)
{
	acpi_status status;
	int i;
	int err;

	input_dev = input_allocate_device();
	if (!input_dev) {
		pr_err("unable to allocate input device\n");
		return -ENOMEM;
	}

	input_dev->name = "Atlas ACPI button driver";
	input_dev->phys = "ASIM0000/atlas/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->keycode = atlas_keymap;
	input_dev->keycodesize = sizeof(unsigned short);
	input_dev->keycodemax = ARRAY_SIZE(atlas_keymap);

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	__set_bit(EV_KEY, input_dev->evbit);
	for (i = 0; i < ARRAY_SIZE(atlas_keymap); i++) {
		if (i < 9) {
			atlas_keymap[i] = KEY_F1 + i;
			__set_bit(KEY_F1 + i, input_dev->keybit);
		} else
			atlas_keymap[i] = KEY_RESERVED;
	}

	err = input_register_device(input_dev);
	if (err) {
		pr_err("couldn't register input device\n");
		input_free_device(input_dev);
		return err;
	}

	/* hookup button handler */
	status = acpi_install_address_space_handler(device->handle,
				0x81, &acpi_atlas_button_handler,
				&acpi_atlas_button_setup, device);
	if (ACPI_FAILURE(status)) {
		pr_err("error installing addr spc handler\n");
		input_unregister_device(input_dev);
		err = -EINVAL;
	}

	return err;
}