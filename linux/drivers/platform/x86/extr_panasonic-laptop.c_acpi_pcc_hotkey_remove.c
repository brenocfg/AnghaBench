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
struct pcc_acpi {struct pcc_acpi* sinf; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  backlight; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct acpi_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pcc_acpi* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  backlight_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pcc_acpi*) ; 
 int /*<<< orphan*/  pcc_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_pcc_hotkey_remove(struct acpi_device *device)
{
	struct pcc_acpi *pcc = acpi_driver_data(device);

	if (!device || !pcc)
		return -EINVAL;

	sysfs_remove_group(&device->dev.kobj, &pcc_attr_group);

	backlight_device_unregister(pcc->backlight);

	input_unregister_device(pcc->input_dev);

	kfree(pcc->sinf);
	kfree(pcc);

	return 0;
}