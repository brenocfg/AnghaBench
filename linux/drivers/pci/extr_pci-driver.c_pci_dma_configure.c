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
struct device {int /*<<< orphan*/  fwnode; TYPE_1__* parent; } ;
struct acpi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int acpi_dma_configure (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_dma_attr (struct acpi_device*) ; 
 scalar_t__ has_acpi_companion (struct device*) ; 
 int of_dma_configure (struct device*,scalar_t__,int) ; 
 struct device* pci_get_host_bridge_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_put_host_bridge_device (struct device*) ; 
 struct acpi_device* to_acpi_device_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static int pci_dma_configure(struct device *dev)
{
	struct device *bridge;
	int ret = 0;

	bridge = pci_get_host_bridge_device(to_pci_dev(dev));

	if (IS_ENABLED(CONFIG_OF) && bridge->parent &&
	    bridge->parent->of_node) {
		ret = of_dma_configure(dev, bridge->parent->of_node, true);
	} else if (has_acpi_companion(bridge)) {
		struct acpi_device *adev = to_acpi_device_node(bridge->fwnode);

		ret = acpi_dma_configure(dev, acpi_get_dma_attr(adev));
	}

	pci_put_host_bridge_device(bridge);
	return ret;
}