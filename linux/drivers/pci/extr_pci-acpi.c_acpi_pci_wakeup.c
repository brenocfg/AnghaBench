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
struct pci_dev {int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int acpi_pci_propagate_wakeup (int /*<<< orphan*/ ,int) ; 
 scalar_t__ acpi_pm_device_can_wakeup (int /*<<< orphan*/ *) ; 
 int acpi_pm_set_device_wakeup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int acpi_pci_wakeup(struct pci_dev *dev, bool enable)
{
	if (acpi_pm_device_can_wakeup(&dev->dev))
		return acpi_pm_set_device_wakeup(&dev->dev, enable);

	return acpi_pci_propagate_wakeup(dev->bus, enable);
}