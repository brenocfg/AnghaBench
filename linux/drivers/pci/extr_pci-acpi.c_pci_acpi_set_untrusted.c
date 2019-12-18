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
typedef  scalar_t__ u8 ;
struct pci_dev {int untrusted; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 scalar_t__ device_property_read_u8 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 

__attribute__((used)) static void pci_acpi_set_untrusted(struct pci_dev *dev)
{
	u8 val;

	if (pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		return;
	if (device_property_read_u8(&dev->dev, "ExternalFacingPort", &val))
		return;

	/*
	 * These root ports expose PCIe (including DMA) outside of the
	 * system so make sure we treat them and everything behind as
	 * untrusted.
	 */
	if (val)
		dev->untrusted = 1;
}