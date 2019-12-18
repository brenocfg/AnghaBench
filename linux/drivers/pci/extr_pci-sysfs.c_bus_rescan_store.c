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
struct pci_bus {int /*<<< orphan*/  self; int /*<<< orphan*/  devices; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_is_root_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_rescan_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_rescan_bus_bridge_resize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 struct pci_bus* to_pci_bus (struct device*) ; 

__attribute__((used)) static ssize_t bus_rescan_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	unsigned long val;
	struct pci_bus *bus = to_pci_bus(dev);

	if (kstrtoul(buf, 0, &val) < 0)
		return -EINVAL;

	if (val) {
		pci_lock_rescan_remove();
		if (!pci_is_root_bus(bus) && list_empty(&bus->devices))
			pci_rescan_bus_bridge_resize(bus->self);
		else
			pci_rescan_bus(bus);
		pci_unlock_rescan_remove();
	}
	return count;
}