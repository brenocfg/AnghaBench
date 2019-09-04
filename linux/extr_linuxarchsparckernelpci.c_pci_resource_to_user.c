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
struct resource {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_bus_region {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcibios_resource_to_bus (int /*<<< orphan*/ ,struct pci_bus_region*,struct resource*) ; 

void pci_resource_to_user(const struct pci_dev *pdev, int bar,
			  const struct resource *rp, resource_size_t *start,
			  resource_size_t *end)
{
	struct pci_bus_region region;

	/*
	 * "User" addresses are shown in /sys/devices/pci.../.../resource
	 * and /proc/bus/pci/devices and used as mmap offsets for
	 * /proc/bus/pci/BB/DD.F files (see proc_bus_pci_mmap()).
	 *
	 * On sparc, these are PCI bus addresses, i.e., raw BAR values.
	 */
	pcibios_resource_to_bus(pdev->bus, &region, (struct resource *) rp);
	*start = region.start;
	*end = region.end;
}