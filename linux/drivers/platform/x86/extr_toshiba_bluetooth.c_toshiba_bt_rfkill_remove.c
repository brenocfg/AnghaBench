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
struct toshiba_bluetooth_dev {scalar_t__ rfk; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 struct toshiba_bluetooth_dev* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  kfree (struct toshiba_bluetooth_dev*) ; 
 int /*<<< orphan*/  rfkill_destroy (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 
 int toshiba_bluetooth_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int toshiba_bt_rfkill_remove(struct acpi_device *device)
{
	struct toshiba_bluetooth_dev *bt_dev = acpi_driver_data(device);

	/* clean up */
	if (bt_dev->rfk) {
		rfkill_unregister(bt_dev->rfk);
		rfkill_destroy(bt_dev->rfk);
	}

	kfree(bt_dev);

	return toshiba_bluetooth_disable(device->handle);
}