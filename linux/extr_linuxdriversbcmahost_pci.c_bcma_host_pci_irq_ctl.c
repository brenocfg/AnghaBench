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
struct pci_dev {int dummy; } ;
struct bcma_device {int /*<<< orphan*/  core_index; } ;
struct bcma_bus {scalar_t__ hosttype; struct pci_dev* host_pci; } ;

/* Variables and functions */
 scalar_t__ BCMA_HOSTTYPE_PCI ; 
 int /*<<< orphan*/  BCMA_PCI_IRQMASK ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

int bcma_host_pci_irq_ctl(struct bcma_bus *bus, struct bcma_device *core,
			  bool enable)
{
	struct pci_dev *pdev;
	u32 coremask, tmp;
	int err = 0;

	if (bus->hosttype != BCMA_HOSTTYPE_PCI) {
		/* This bcma device is not on a PCI host-bus. So the IRQs are
		 * not routed through the PCI core.
		 * So we must not enable routing through the PCI core. */
		goto out;
	}

	pdev = bus->host_pci;

	err = pci_read_config_dword(pdev, BCMA_PCI_IRQMASK, &tmp);
	if (err)
		goto out;

	coremask = BIT(core->core_index) << 8;
	if (enable)
		tmp |= coremask;
	else
		tmp &= ~coremask;

	err = pci_write_config_dword(pdev, BCMA_PCI_IRQMASK, tmp);

out:
	return err;
}