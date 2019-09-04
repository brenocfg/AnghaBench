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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {int number; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PCIBIOS_FUNC_NOT_SUPPORTED ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  cvmx_pcie_config_write16 (unsigned int,int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pcie_config_write32 (unsigned int,int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pcie_config_write8 (unsigned int,int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__* enable_pcie_bus_num_war ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int,unsigned int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int octeon_pcie_write_config(unsigned int pcie_port, struct pci_bus *bus,
				    unsigned int devfn, int reg,
				    int size, u32 val)
{
	int bus_number = bus->number;

	BUG_ON(pcie_port >= ARRAY_SIZE(enable_pcie_bus_num_war));

	if ((bus->parent == NULL) && (enable_pcie_bus_num_war[pcie_port]))
		bus_number = 0;

	pr_debug("pcie_cfg_wr port=%d b=%d devfn=0x%03x"
		 " reg=0x%03x size=%d val=%08x\n", pcie_port, bus_number, devfn,
		 reg, size, val);


	switch (size) {
	case 4:
		cvmx_pcie_config_write32(pcie_port, bus_number, devfn >> 3,
					 devfn & 0x7, reg, val);
		break;
	case 2:
		cvmx_pcie_config_write16(pcie_port, bus_number, devfn >> 3,
					 devfn & 0x7, reg, val);
		break;
	case 1:
		cvmx_pcie_config_write8(pcie_port, bus_number, devfn >> 3,
					devfn & 0x7, reg, val);
		break;
	default:
		return PCIBIOS_FUNC_NOT_SUPPORTED;
	}
	return PCIBIOS_SUCCESSFUL;
}