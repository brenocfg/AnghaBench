#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcc_acpi {struct input_dev* input_dev; } ;
struct TYPE_2__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct input_dev {TYPE_1__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ERROR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PCC_DRIVER_NAME ; 
 int /*<<< orphan*/  ACPI_PCC_INPUT_PHYS ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  panasonic_keymap ; 
 int sparse_keymap_setup (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_pcc_init_input(struct pcc_acpi *pcc)
{
	struct input_dev *input_dev;
	int error;

	input_dev = input_allocate_device();
	if (!input_dev)
		return -ENOMEM;

	input_dev->name = ACPI_PCC_DRIVER_NAME;
	input_dev->phys = ACPI_PCC_INPUT_PHYS;
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendor = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;

	error = sparse_keymap_setup(input_dev, panasonic_keymap, NULL);
	if (error) {
		ACPI_DEBUG_PRINT((ACPI_DB_ERROR,
				  "Unable to setup input device keymap\n"));
		goto err_free_dev;
	}

	error = input_register_device(input_dev);
	if (error) {
		ACPI_DEBUG_PRINT((ACPI_DB_ERROR,
				  "Unable to register input device\n"));
		goto err_free_dev;
	}

	pcc->input_dev = input_dev;
	return 0;

 err_free_dev:
	input_free_device(input_dev);
	return error;
}