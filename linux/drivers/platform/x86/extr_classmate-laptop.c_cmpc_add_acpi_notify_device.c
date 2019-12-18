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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {char* name; TYPE_1__ dev; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  (* input_device_init ) (struct input_dev*) ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct input_dev*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 

__attribute__((used)) static int cmpc_add_acpi_notify_device(struct acpi_device *acpi, char *name,
				       input_device_init idev_init)
{
	struct input_dev *inputdev;
	int error;

	inputdev = input_allocate_device();
	if (!inputdev)
		return -ENOMEM;
	inputdev->name = name;
	inputdev->dev.parent = &acpi->dev;
	idev_init(inputdev);
	error = input_register_device(inputdev);
	if (error) {
		input_free_device(inputdev);
		return error;
	}
	dev_set_drvdata(&acpi->dev, inputdev);
	return 0;
}