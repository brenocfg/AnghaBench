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
struct rcar_pcie {int dummy; } ;
struct pci_bus {int /*<<< orphan*/  number; int /*<<< orphan*/  dev; struct rcar_pcie* sysdata; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  RCAR_PCI_ACCESS_READ ; 
 int /*<<< orphan*/  RCAR_PCI_ACCESS_WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 
 int rcar_pcie_config_access (struct rcar_pcie*,int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int*) ; 

__attribute__((used)) static int rcar_pcie_write_conf(struct pci_bus *bus, unsigned int devfn,
				int where, int size, u32 val)
{
	struct rcar_pcie *pcie = bus->sysdata;
	unsigned int shift;
	u32 data;
	int ret;

	ret = rcar_pcie_config_access(pcie, RCAR_PCI_ACCESS_READ,
				      bus, devfn, where, &data);
	if (ret != PCIBIOS_SUCCESSFUL)
		return ret;

	dev_dbg(&bus->dev, "pcie-config-write: bus=%3d devfn=0x%04x where=0x%04x size=%d val=0x%08x\n",
		bus->number, devfn, where, size, val);

	if (size == 1) {
		shift = BITS_PER_BYTE * (where & 3);
		data &= ~(0xff << shift);
		data |= ((val & 0xff) << shift);
	} else if (size == 2) {
		shift = BITS_PER_BYTE * (where & 2);
		data &= ~(0xffff << shift);
		data |= ((val & 0xffff) << shift);
	} else
		data = val;

	ret = rcar_pcie_config_access(pcie, RCAR_PCI_ACCESS_WRITE,
				      bus, devfn, where, &data);

	return ret;
}