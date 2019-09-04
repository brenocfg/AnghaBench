#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phantom_device {scalar_t__ caddr; scalar_t__ iaddr; scalar_t__ oaddr; TYPE_1__ cdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 unsigned int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ PHN_IRQCTL ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct phantom_device*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct phantom_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct phantom_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  phantom_class ; 
 scalar_t__* phantom_devices ; 
 int /*<<< orphan*/  phantom_major ; 

__attribute__((used)) static void phantom_remove(struct pci_dev *pdev)
{
	struct phantom_device *pht = pci_get_drvdata(pdev);
	unsigned int minor = MINOR(pht->cdev.dev);

	device_destroy(phantom_class, MKDEV(phantom_major, minor));

	cdev_del(&pht->cdev);

	iowrite32(0, pht->caddr + PHN_IRQCTL);
	ioread32(pht->caddr + PHN_IRQCTL); /* PCI posting */
	free_irq(pdev->irq, pht);

	pci_iounmap(pdev, pht->oaddr);
	pci_iounmap(pdev, pht->iaddr);
	pci_iounmap(pdev, pht->caddr);

	kfree(pht);

	pci_release_regions(pdev);

	phantom_devices[minor] = 0;

	pci_disable_device(pdev);
}