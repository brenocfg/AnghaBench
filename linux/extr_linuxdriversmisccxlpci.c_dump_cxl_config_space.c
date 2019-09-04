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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCI_BASE_ADDRESS_0 ; 
 int PCI_BASE_ADDRESS_1 ; 
 int PCI_BASE_ADDRESS_2 ; 
 int PCI_BASE_ADDRESS_3 ; 
 int PCI_BASE_ADDRESS_4 ; 
 int PCI_BASE_ADDRESS_5 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int find_cxl_vsec (struct pci_dev*) ; 
 char* p1_base (struct pci_dev*) ; 
 int p1_size (struct pci_dev*) ; 
 char* p2_base (struct pci_dev*) ; 
 int p2_size (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int pci_resource_len (struct pci_dev*,int) ; 
 char* pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static void dump_cxl_config_space(struct pci_dev *dev)
{
	int vsec;
	u32 val;

	dev_info(&dev->dev, "dump_cxl_config_space\n");

	pci_read_config_dword(dev, PCI_BASE_ADDRESS_0, &val);
	dev_info(&dev->dev, "BAR0: %#.8x\n", val);
	pci_read_config_dword(dev, PCI_BASE_ADDRESS_1, &val);
	dev_info(&dev->dev, "BAR1: %#.8x\n", val);
	pci_read_config_dword(dev, PCI_BASE_ADDRESS_2, &val);
	dev_info(&dev->dev, "BAR2: %#.8x\n", val);
	pci_read_config_dword(dev, PCI_BASE_ADDRESS_3, &val);
	dev_info(&dev->dev, "BAR3: %#.8x\n", val);
	pci_read_config_dword(dev, PCI_BASE_ADDRESS_4, &val);
	dev_info(&dev->dev, "BAR4: %#.8x\n", val);
	pci_read_config_dword(dev, PCI_BASE_ADDRESS_5, &val);
	dev_info(&dev->dev, "BAR5: %#.8x\n", val);

	dev_info(&dev->dev, "p1 regs: %#llx, len: %#llx\n",
		p1_base(dev), p1_size(dev));
	dev_info(&dev->dev, "p2 regs: %#llx, len: %#llx\n",
		p2_base(dev), p2_size(dev));
	dev_info(&dev->dev, "BAR 4/5: %#llx, len: %#llx\n",
		pci_resource_start(dev, 4), pci_resource_len(dev, 4));

	if (!(vsec = find_cxl_vsec(dev)))
		return;

#define show_reg(name, what) \
	dev_info(&dev->dev, "cxl vsec: %30s: %#x\n", name, what)

	pci_read_config_dword(dev, vsec + 0x0, &val);
	show_reg("Cap ID", (val >> 0) & 0xffff);
	show_reg("Cap Ver", (val >> 16) & 0xf);
	show_reg("Next Cap Ptr", (val >> 20) & 0xfff);
	pci_read_config_dword(dev, vsec + 0x4, &val);
	show_reg("VSEC ID", (val >> 0) & 0xffff);
	show_reg("VSEC Rev", (val >> 16) & 0xf);
	show_reg("VSEC Length",	(val >> 20) & 0xfff);
	pci_read_config_dword(dev, vsec + 0x8, &val);
	show_reg("Num AFUs", (val >> 0) & 0xff);
	show_reg("Status", (val >> 8) & 0xff);
	show_reg("Mode Control", (val >> 16) & 0xff);
	show_reg("Reserved", (val >> 24) & 0xff);
	pci_read_config_dword(dev, vsec + 0xc, &val);
	show_reg("PSL Rev", (val >> 0) & 0xffff);
	show_reg("CAIA Ver", (val >> 16) & 0xffff);
	pci_read_config_dword(dev, vsec + 0x10, &val);
	show_reg("Base Image Rev", (val >> 0) & 0xffff);
	show_reg("Reserved", (val >> 16) & 0x0fff);
	show_reg("Image Control", (val >> 28) & 0x3);
	show_reg("Reserved", (val >> 30) & 0x1);
	show_reg("Image Loaded", (val >> 31) & 0x1);

	pci_read_config_dword(dev, vsec + 0x14, &val);
	show_reg("Reserved", val);
	pci_read_config_dword(dev, vsec + 0x18, &val);
	show_reg("Reserved", val);
	pci_read_config_dword(dev, vsec + 0x1c, &val);
	show_reg("Reserved", val);

	pci_read_config_dword(dev, vsec + 0x20, &val);
	show_reg("AFU Descriptor Offset", val);
	pci_read_config_dword(dev, vsec + 0x24, &val);
	show_reg("AFU Descriptor Size", val);
	pci_read_config_dword(dev, vsec + 0x28, &val);
	show_reg("Problem State Offset", val);
	pci_read_config_dword(dev, vsec + 0x2c, &val);
	show_reg("Problem State Size", val);

	pci_read_config_dword(dev, vsec + 0x30, &val);
	show_reg("Reserved", val);
	pci_read_config_dword(dev, vsec + 0x34, &val);
	show_reg("Reserved", val);
	pci_read_config_dword(dev, vsec + 0x38, &val);
	show_reg("Reserved", val);
	pci_read_config_dword(dev, vsec + 0x3c, &val);
	show_reg("Reserved", val);

	pci_read_config_dword(dev, vsec + 0x40, &val);
	show_reg("PSL Programming Port", val);
	pci_read_config_dword(dev, vsec + 0x44, &val);
	show_reg("PSL Programming Control", val);

	pci_read_config_dword(dev, vsec + 0x48, &val);
	show_reg("Reserved", val);
	pci_read_config_dword(dev, vsec + 0x4c, &val);
	show_reg("Reserved", val);

	pci_read_config_dword(dev, vsec + 0x50, &val);
	show_reg("Flash Address Register", val);
	pci_read_config_dword(dev, vsec + 0x54, &val);
	show_reg("Flash Size Register", val);
	pci_read_config_dword(dev, vsec + 0x58, &val);
	show_reg("Flash Status/Control Register", val);
	pci_read_config_dword(dev, vsec + 0x58, &val);
	show_reg("Flash Data Port", val);

#undef show_reg
}