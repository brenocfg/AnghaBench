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
struct TYPE_2__ {int product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; char* phys; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_1__ id; } ;
struct acpi_device {struct input_dev* driver_data; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  KEY_RFKILL ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_AI ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acer_wireless_add(struct acpi_device *adev)
{
	struct input_dev *idev;

	idev = devm_input_allocate_device(&adev->dev);
	if (!idev)
		return -ENOMEM;

	adev->driver_data = idev;
	idev->name = "Acer Wireless Radio Control";
	idev->phys = "acer-wireless/input0";
	idev->id.bustype = BUS_HOST;
	idev->id.vendor = PCI_VENDOR_ID_AI;
	idev->id.product = 0x1229;
	set_bit(EV_KEY, idev->evbit);
	set_bit(KEY_RFKILL, idev->keybit);

	return input_register_device(idev);
}