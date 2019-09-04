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
union pci_config_address {int register_number; unsigned int devfn_number; int enable_bit; int /*<<< orphan*/  w; int /*<<< orphan*/  bus_number; } ;
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CONFIG_ADDRESS ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_virtio_guest_write_config_addr(struct pci_bus *bus,
					unsigned int devfn, int reg)
{
	union pci_config_address pca = { .w = 0 };

	pca.register_number = reg;
	pca.devfn_number = devfn;
	pca.bus_number = bus->number;
	pca.enable_bit = 1;

	outl(pca.w, PCI_CONFIG_ADDRESS);
}