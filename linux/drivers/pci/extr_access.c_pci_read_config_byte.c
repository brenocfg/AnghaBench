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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int pci_bus_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_dev_is_disconnected (struct pci_dev const*) ; 

int pci_read_config_byte(const struct pci_dev *dev, int where, u8 *val)
{
	if (pci_dev_is_disconnected(dev)) {
		*val = ~0;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}
	return pci_bus_read_config_byte(dev->bus, dev->devfn, where, val);
}