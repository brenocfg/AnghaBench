#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct cx88_core {int /*<<< orphan*/  pci_irqmask; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  active; } ;
struct cx8802_dev {TYPE_2__* pci; struct cx88_core* core; TYPE_1__ mpegq; int /*<<< orphan*/  slock; int /*<<< orphan*/  pci_lat; int /*<<< orphan*/  pci_rev; } ;
struct TYPE_10__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  MO_PCI_INTMSK ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  cx8802_irq ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_enable_device (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_name (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_read_config_byte (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_resource_start (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (TYPE_2__*,struct cx8802_dev*) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cx8802_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx8802_init_common(struct cx8802_dev *dev)
{
	struct cx88_core *core = dev->core;
	int err;

	/* pci init */
	if (pci_enable_device(dev->pci))
		return -EIO;
	pci_set_master(dev->pci);
	err = pci_set_dma_mask(dev->pci, DMA_BIT_MASK(32));
	if (err) {
		pr_err("Oops: no 32bit PCI DMA ???\n");
		return -EIO;
	}

	dev->pci_rev = dev->pci->revision;
	pci_read_config_byte(dev->pci, PCI_LATENCY_TIMER,  &dev->pci_lat);
	pr_info("found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
		pci_name(dev->pci), dev->pci_rev, dev->pci->irq,
		dev->pci_lat,
		(unsigned long long)pci_resource_start(dev->pci, 0));

	/* initialize driver struct */
	spin_lock_init(&dev->slock);

	/* init dma queue */
	INIT_LIST_HEAD(&dev->mpegq.active);

	/* get irq */
	err = request_irq(dev->pci->irq, cx8802_irq,
			  IRQF_SHARED, dev->core->name, dev);
	if (err < 0) {
		pr_err("can't get IRQ %d\n", dev->pci->irq);
		return err;
	}
	cx_set(MO_PCI_INTMSK, core->pci_irqmask);

	/* everything worked */
	pci_set_drvdata(dev->pci, dev);
	return 0;
}