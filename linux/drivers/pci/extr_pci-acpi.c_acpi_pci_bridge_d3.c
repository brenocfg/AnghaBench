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
typedef  int u8 ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  is_hotplug_bridge; } ;
struct fwnode_handle {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 struct fwnode_handle* acpi_fwnode_handle (struct acpi_device*) ; 
 struct acpi_device* acpi_pci_find_companion (int /*<<< orphan*/ *) ; 
 scalar_t__ fwnode_property_read_u8 (struct fwnode_handle const*,char*,int*) ; 
 int /*<<< orphan*/  pci_dev_is_added (struct pci_dev*) ; 
 struct pci_dev* pci_find_pcie_root_port (struct pci_dev*) ; 

__attribute__((used)) static bool acpi_pci_bridge_d3(struct pci_dev *dev)
{
	const struct fwnode_handle *fwnode;
	struct acpi_device *adev;
	struct pci_dev *root;
	u8 val;

	if (!dev->is_hotplug_bridge)
		return false;

	/*
	 * Look for a special _DSD property for the root port and if it
	 * is set we know the hierarchy behind it supports D3 just fine.
	 */
	root = pci_find_pcie_root_port(dev);
	if (!root)
		return false;

	adev = ACPI_COMPANION(&root->dev);
	if (root == dev) {
		/*
		 * It is possible that the ACPI companion is not yet bound
		 * for the root port so look it up manually here.
		 */
		if (!adev && !pci_dev_is_added(root))
			adev = acpi_pci_find_companion(&root->dev);
	}

	if (!adev)
		return false;

	fwnode = acpi_fwnode_handle(adev);
	if (fwnode_property_read_u8(fwnode, "HotPlugSupportInD3", &val))
		return false;

	return val == 1;
}