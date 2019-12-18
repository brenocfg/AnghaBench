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
struct r852_device {struct r852_device* chip; int /*<<< orphan*/  phys_bounce_buffer; int /*<<< orphan*/  bounce_buffer; int /*<<< orphan*/  mmio; struct r852_device* tmp_buffer; int /*<<< orphan*/  irq; int /*<<< orphan*/  card_workqueue; int /*<<< orphan*/  card_detect_work; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  R852_DMA_LEN ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct r852_device*) ; 
 int /*<<< orphan*/  kfree (struct r852_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct r852_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  r852_disable_irqs (struct r852_device*) ; 
 int /*<<< orphan*/  r852_unregister_nand_device (struct r852_device*) ; 

__attribute__((used)) static void r852_remove(struct pci_dev *pci_dev)
{
	struct r852_device *dev = pci_get_drvdata(pci_dev);

	/* Stop detect workqueue -
		we are going to unregister the device anyway*/
	cancel_delayed_work_sync(&dev->card_detect_work);
	destroy_workqueue(dev->card_workqueue);

	/* Unregister the device, this might make more IO */
	r852_unregister_nand_device(dev);

	/* Stop interrupts */
	r852_disable_irqs(dev);
	free_irq(dev->irq, dev);

	/* Cleanup */
	kfree(dev->tmp_buffer);
	pci_iounmap(pci_dev, dev->mmio);
	dma_free_coherent(&pci_dev->dev, R852_DMA_LEN, dev->bounce_buffer,
			  dev->phys_bounce_buffer);

	kfree(dev->chip);
	kfree(dev);

	/* Shutdown the PCI device */
	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);
}