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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct cx25821_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  name; scalar_t__ base_io_addr; int /*<<< orphan*/  pci_lat; int /*<<< orphan*/  pci_rev; struct pci_dev* pci; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int cx25821_dev_setup (struct cx25821_dev*) ; 
 int /*<<< orphan*/  cx25821_dev_unregister (struct cx25821_dev*) ; 
 int /*<<< orphan*/  cx25821_irq ; 
 int /*<<< orphan*/  kfree (struct cx25821_dev*) ; 
 struct cx25821_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_set_dma_mask (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cx25821_dev*) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx25821_initdev(struct pci_dev *pci_dev,
			   const struct pci_device_id *pci_id)
{
	struct cx25821_dev *dev;
	int err = 0;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (NULL == dev)
		return -ENOMEM;

	err = v4l2_device_register(&pci_dev->dev, &dev->v4l2_dev);
	if (err < 0)
		goto fail_free;

	/* pci init */
	dev->pci = pci_dev;
	if (pci_enable_device(pci_dev)) {
		err = -EIO;

		pr_info("pci enable failed!\n");

		goto fail_unregister_device;
	}

	err = cx25821_dev_setup(dev);
	if (err)
		goto fail_unregister_pci;

	/* print pci info */
	pci_read_config_byte(pci_dev, PCI_CLASS_REVISION, &dev->pci_rev);
	pci_read_config_byte(pci_dev, PCI_LATENCY_TIMER, &dev->pci_lat);
	pr_info("%s/0: found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
		dev->name, pci_name(pci_dev), dev->pci_rev, pci_dev->irq,
		dev->pci_lat, (unsigned long long)dev->base_io_addr);

	pci_set_master(pci_dev);
	err = pci_set_dma_mask(pci_dev, 0xffffffff);
	if (err) {
		pr_err("%s/0: Oops: no 32bit PCI DMA ???\n", dev->name);
		err = -EIO;
		goto fail_irq;
	}

	err = request_irq(pci_dev->irq, cx25821_irq,
			IRQF_SHARED, dev->name, dev);

	if (err < 0) {
		pr_err("%s: can't get IRQ %d\n", dev->name, pci_dev->irq);
		goto fail_irq;
	}

	return 0;

fail_irq:
	pr_info("cx25821_initdev() can't get IRQ !\n");
	cx25821_dev_unregister(dev);

fail_unregister_pci:
	pci_disable_device(pci_dev);
fail_unregister_device:
	v4l2_device_unregister(&dev->v4l2_dev);

fail_free:
	kfree(dev);
	return err;
}