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
struct pci_dev {scalar_t__ bridge_d3; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  valid; } ;
struct TYPE_4__ {TYPE_1__ flags; } ;
struct acpi_device {TYPE_2__ wakeup; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  acpi_device_power_add_dependent (struct acpi_device*,struct device*) ; 
 int /*<<< orphan*/  acpi_pci_wakeup (struct pci_dev*,int) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (struct device*,int) ; 
 int /*<<< orphan*/  device_wakeup_enable (struct device*) ; 
 int /*<<< orphan*/  pci_acpi_add_pm_notifier (struct acpi_device*,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_acpi_optimize_delay (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_acpi_set_untrusted (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static void pci_acpi_setup(struct device *dev)
{
	struct pci_dev *pci_dev = to_pci_dev(dev);
	struct acpi_device *adev = ACPI_COMPANION(dev);

	if (!adev)
		return;

	pci_acpi_optimize_delay(pci_dev, adev->handle);
	pci_acpi_set_untrusted(pci_dev);

	pci_acpi_add_pm_notifier(adev, pci_dev);
	if (!adev->wakeup.flags.valid)
		return;

	device_set_wakeup_capable(dev, true);
	/*
	 * For bridges that can do D3 we enable wake automatically (as
	 * we do for the power management itself in that case). The
	 * reason is that the bridge may have additional methods such as
	 * _DSW that need to be called.
	 */
	if (pci_dev->bridge_d3)
		device_wakeup_enable(dev);

	acpi_pci_wakeup(pci_dev, false);
	acpi_device_power_add_dependent(adev, dev);
}