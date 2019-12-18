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
struct pci_bus {int dummy; } ;
struct bus_type {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct pci_bus* pci_find_next_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_rescan_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 

__attribute__((used)) static ssize_t rescan_store(struct bus_type *bus, const char *buf, size_t count)
{
	unsigned long val;
	struct pci_bus *b = NULL;

	if (kstrtoul(buf, 0, &val) < 0)
		return -EINVAL;

	if (val) {
		pci_lock_rescan_remove();
		while ((b = pci_find_next_bus(b)) != NULL)
			pci_rescan_bus(b);
		pci_unlock_rescan_remove();
	}
	return count;
}