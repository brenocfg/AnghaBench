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
typedef  void* ulong ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct brcmf_pciedev_info {unsigned long long tcm; void* regs; struct pci_dev* pdev; } ;
struct brcmf_bus {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 void* BRCMF_PCIE_REG_MAP_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,...) ; 
 int /*<<< orphan*/  brcmf_err (struct brcmf_bus*,char*,int,...) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 void* ioremap_nocache (scalar_t__,void*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 void* pci_resource_len (struct pci_dev*,int) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static int brcmf_pcie_get_resource(struct brcmf_pciedev_info *devinfo)
{
	struct pci_dev *pdev = devinfo->pdev;
	struct brcmf_bus *bus = dev_get_drvdata(&pdev->dev);
	int err;
	phys_addr_t  bar0_addr, bar1_addr;
	ulong bar1_size;

	err = pci_enable_device(pdev);
	if (err) {
		brcmf_err(bus, "pci_enable_device failed err=%d\n", err);
		return err;
	}

	pci_set_master(pdev);

	/* Bar-0 mapped address */
	bar0_addr = pci_resource_start(pdev, 0);
	/* Bar-1 mapped address */
	bar1_addr = pci_resource_start(pdev, 2);
	/* read Bar-1 mapped memory range */
	bar1_size = pci_resource_len(pdev, 2);
	if ((bar1_size == 0) || (bar1_addr == 0)) {
		brcmf_err(bus, "BAR1 Not enabled, device size=%ld, addr=%#016llx\n",
			  bar1_size, (unsigned long long)bar1_addr);
		return -EINVAL;
	}

	devinfo->regs = ioremap_nocache(bar0_addr, BRCMF_PCIE_REG_MAP_SIZE);
	devinfo->tcm = ioremap_nocache(bar1_addr, bar1_size);

	if (!devinfo->regs || !devinfo->tcm) {
		brcmf_err(bus, "ioremap() failed (%p,%p)\n", devinfo->regs,
			  devinfo->tcm);
		return -EINVAL;
	}
	brcmf_dbg(PCIE, "Phys addr : reg space = %p base addr %#016llx\n",
		  devinfo->regs, (unsigned long long)bar0_addr);
	brcmf_dbg(PCIE, "Phys addr : mem space = %p base addr %#016llx size 0x%x\n",
		  devinfo->tcm, (unsigned long long)bar1_addr,
		  (unsigned int)bar1_size);

	return 0;
}