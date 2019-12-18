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
typedef  int u64 ;
typedef  int u32 ;
struct resource {int start; int end; unsigned long flags; int /*<<< orphan*/  name; } ;
struct pci_dev {int dummy; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 unsigned long IORESOURCE_MEM_64 ; 
 int PCI_EA_BEI ; 
 int PCI_EA_BEI_BAR5 ; 
 int PCI_EA_BEI_ROM ; 
 int PCI_EA_BEI_VF_BAR0 ; 
 int PCI_EA_BEI_VF_BAR5 ; 
 int PCI_EA_ENABLE ; 
 int PCI_EA_ES ; 
 int PCI_EA_FIELD_MASK ; 
 int PCI_EA_IS_64 ; 
 int PCI_EA_PP ; 
 int PCI_EA_P_BRIDGE_IO ; 
 int PCI_EA_P_MEM_RESERVED ; 
 int PCI_EA_SP ; 
 unsigned long pci_ea_flags (struct pci_dev*,int) ; 
 struct resource* pci_ea_get_resource (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,...) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,...) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 

__attribute__((used)) static int pci_ea_read(struct pci_dev *dev, int offset)
{
	struct resource *res;
	int ent_size, ent_offset = offset;
	resource_size_t start, end;
	unsigned long flags;
	u32 dw0, bei, base, max_offset;
	u8 prop;
	bool support_64 = (sizeof(resource_size_t) >= 8);

	pci_read_config_dword(dev, ent_offset, &dw0);
	ent_offset += 4;

	/* Entry size field indicates DWORDs after 1st */
	ent_size = ((dw0 & PCI_EA_ES) + 1) << 2;

	if (!(dw0 & PCI_EA_ENABLE)) /* Entry not enabled */
		goto out;

	bei = (dw0 & PCI_EA_BEI) >> 4;
	prop = (dw0 & PCI_EA_PP) >> 8;

	/*
	 * If the Property is in the reserved range, try the Secondary
	 * Property instead.
	 */
	if (prop > PCI_EA_P_BRIDGE_IO && prop < PCI_EA_P_MEM_RESERVED)
		prop = (dw0 & PCI_EA_SP) >> 16;
	if (prop > PCI_EA_P_BRIDGE_IO)
		goto out;

	res = pci_ea_get_resource(dev, bei, prop);
	if (!res) {
		pci_err(dev, "Unsupported EA entry BEI: %u\n", bei);
		goto out;
	}

	flags = pci_ea_flags(dev, prop);
	if (!flags) {
		pci_err(dev, "Unsupported EA properties: %#x\n", prop);
		goto out;
	}

	/* Read Base */
	pci_read_config_dword(dev, ent_offset, &base);
	start = (base & PCI_EA_FIELD_MASK);
	ent_offset += 4;

	/* Read MaxOffset */
	pci_read_config_dword(dev, ent_offset, &max_offset);
	ent_offset += 4;

	/* Read Base MSBs (if 64-bit entry) */
	if (base & PCI_EA_IS_64) {
		u32 base_upper;

		pci_read_config_dword(dev, ent_offset, &base_upper);
		ent_offset += 4;

		flags |= IORESOURCE_MEM_64;

		/* entry starts above 32-bit boundary, can't use */
		if (!support_64 && base_upper)
			goto out;

		if (support_64)
			start |= ((u64)base_upper << 32);
	}

	end = start + (max_offset | 0x03);

	/* Read MaxOffset MSBs (if 64-bit entry) */
	if (max_offset & PCI_EA_IS_64) {
		u32 max_offset_upper;

		pci_read_config_dword(dev, ent_offset, &max_offset_upper);
		ent_offset += 4;

		flags |= IORESOURCE_MEM_64;

		/* entry too big, can't use */
		if (!support_64 && max_offset_upper)
			goto out;

		if (support_64)
			end += ((u64)max_offset_upper << 32);
	}

	if (end < start) {
		pci_err(dev, "EA Entry crosses address boundary\n");
		goto out;
	}

	if (ent_size != ent_offset - offset) {
		pci_err(dev, "EA Entry Size (%d) does not match length read (%d)\n",
			ent_size, ent_offset - offset);
		goto out;
	}

	res->name = pci_name(dev);
	res->start = start;
	res->end = end;
	res->flags = flags;

	if (bei <= PCI_EA_BEI_BAR5)
		pci_info(dev, "BAR %d: %pR (from Enhanced Allocation, properties %#02x)\n",
			   bei, res, prop);
	else if (bei == PCI_EA_BEI_ROM)
		pci_info(dev, "ROM: %pR (from Enhanced Allocation, properties %#02x)\n",
			   res, prop);
	else if (bei >= PCI_EA_BEI_VF_BAR0 && bei <= PCI_EA_BEI_VF_BAR5)
		pci_info(dev, "VF BAR %d: %pR (from Enhanced Allocation, properties %#02x)\n",
			   bei - PCI_EA_BEI_VF_BAR0, res, prop);
	else
		pci_info(dev, "BEI %d res: %pR (from Enhanced Allocation, properties %#02x)\n",
			   bei, res, prop);

out:
	return offset + ent_size;
}