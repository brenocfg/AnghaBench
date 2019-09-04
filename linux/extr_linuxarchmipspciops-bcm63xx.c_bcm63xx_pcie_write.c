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
typedef  int u32 ;
struct pci_bus {scalar_t__ number; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 scalar_t__ PCIE_BUS_DEVICE ; 
 scalar_t__ PCIE_DEVICE_OFFSET ; 
 int /*<<< orphan*/  bcm63xx_pcie_can_access (struct pci_bus*,unsigned int) ; 
 int bcm_pcie_readl (int) ; 
 int /*<<< orphan*/  bcm_pcie_writel (int,int) ; 
 int preprocess_write (int,int,int,int) ; 

__attribute__((used)) static int bcm63xx_pcie_write(struct pci_bus *bus, unsigned int devfn,
			      int where, int size, u32 val)
{
	u32 data;
	u32 reg = where & ~3;

	if (!bcm63xx_pcie_can_access(bus, devfn))
		return PCIBIOS_DEVICE_NOT_FOUND;

	if (bus->number == PCIE_BUS_DEVICE)
		reg += PCIE_DEVICE_OFFSET;


	data = bcm_pcie_readl(reg);

	data = preprocess_write(data, val, where, size);
	bcm_pcie_writel(data, reg);

	return PCIBIOS_SUCCESSFUL;
}