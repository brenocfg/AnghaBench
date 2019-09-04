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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct ata_ioports {scalar_t__ bmdma_addr; scalar_t__ ctl_addr; scalar_t__ cmd_addr; scalar_t__ altstatus_addr; } ;
struct ata_port {struct ata_ioports ioaddr; } ;
struct ata_host {int n_ports; struct ata_port** ports; int /*<<< orphan*/  iomap; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DMA_MASK ; 
 int ATP867X_BAR_IOBASE ; 
 scalar_t__ ATP867X_IO_ALTSTATUS (struct ata_port*,int) ; 
 scalar_t__ ATP867X_IO_DMABASE (struct ata_port*,int) ; 
 scalar_t__ ATP867X_IO_PORTBASE (struct ata_port*,int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  ata_port_desc (struct ata_port*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  ata_sff_std_ports (struct ata_ioports*) ; 
 int /*<<< orphan*/  atp867x_fixup (struct ata_host*) ; 
 int atp867x_set_priv (struct ata_port*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pcim_iomap_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_pin_device (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int atp867x_ata_pci_sff_init_host(struct ata_host *host)
{
	struct device *gdev = host->dev;
	struct pci_dev *pdev = to_pci_dev(gdev);
	unsigned int mask = 0;
	int i, rc;

	/*
	 * do not map rombase
	 */
	rc = pcim_iomap_regions(pdev, 1 << ATP867X_BAR_IOBASE, DRV_NAME);
	if (rc == -EBUSY)
		pcim_pin_device(pdev);
	if (rc)
		return rc;
	host->iomap = pcim_iomap_table(pdev);

#ifdef	ATP867X_DEBUG
	atp867x_check_res(pdev);

	for (i = 0; i < PCI_ROM_RESOURCE; i++)
		printk(KERN_DEBUG "ATP867X: iomap[%d]=0x%llx\n", i,
			(unsigned long long)(host->iomap[i]));
#endif

	/*
	 * request, iomap BARs and init port addresses accordingly
	 */
	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];
		struct ata_ioports *ioaddr = &ap->ioaddr;

		ioaddr->cmd_addr = ATP867X_IO_PORTBASE(ap, i);
		ioaddr->ctl_addr = ioaddr->altstatus_addr
				 = ATP867X_IO_ALTSTATUS(ap, i);
		ioaddr->bmdma_addr = ATP867X_IO_DMABASE(ap, i);

		ata_sff_std_ports(ioaddr);
		rc = atp867x_set_priv(ap);
		if (rc)
			return rc;

#ifdef	ATP867X_DEBUG
		atp867x_check_ports(ap, i);
#endif
		ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx",
			(unsigned long)ioaddr->cmd_addr,
			(unsigned long)ioaddr->ctl_addr);
		ata_port_desc(ap, "bmdma 0x%lx",
			(unsigned long)ioaddr->bmdma_addr);

		mask |= 1 << i;
	}

	if (!mask) {
		dev_err(gdev, "no available native port\n");
		return -ENODEV;
	}

	atp867x_fixup(host);

	rc = dma_set_mask(&pdev->dev, ATA_DMA_MASK);
	if (rc)
		return rc;

	rc = dma_set_coherent_mask(&pdev->dev, ATA_DMA_MASK);
	return rc;
}