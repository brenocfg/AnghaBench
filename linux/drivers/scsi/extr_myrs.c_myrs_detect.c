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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct myrs_privdata {unsigned int mmio_size; scalar_t__ (* hw_init ) (struct pci_dev*,struct myrs_hba*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  irq_handler; } ;
struct myrs_hba {int pci_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/ * io_base; int /*<<< orphan*/ * mmio_base; int /*<<< orphan*/  queue_lock; struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int PAGE_MASK ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * ioremap_nocache (int,unsigned int) ; 
 struct myrs_hba* myrs_alloc_host (struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  myrs_cleanup (struct myrs_hba*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct myrs_hba*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct myrs_hba*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct pci_dev*,struct myrs_hba*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct myrs_hba *myrs_detect(struct pci_dev *pdev,
		const struct pci_device_id *entry)
{
	struct myrs_privdata *privdata =
		(struct myrs_privdata *)entry->driver_data;
	irq_handler_t irq_handler = privdata->irq_handler;
	unsigned int mmio_size = privdata->mmio_size;
	struct myrs_hba *cs = NULL;

	cs = myrs_alloc_host(pdev, entry);
	if (!cs) {
		dev_err(&pdev->dev, "Unable to allocate Controller\n");
		return NULL;
	}
	cs->pdev = pdev;

	if (pci_enable_device(pdev))
		goto Failure;

	cs->pci_addr = pci_resource_start(pdev, 0);

	pci_set_drvdata(pdev, cs);
	spin_lock_init(&cs->queue_lock);
	/* Map the Controller Register Window. */
	if (mmio_size < PAGE_SIZE)
		mmio_size = PAGE_SIZE;
	cs->mmio_base = ioremap_nocache(cs->pci_addr & PAGE_MASK, mmio_size);
	if (cs->mmio_base == NULL) {
		dev_err(&pdev->dev,
			"Unable to map Controller Register Window\n");
		goto Failure;
	}

	cs->io_base = cs->mmio_base + (cs->pci_addr & ~PAGE_MASK);
	if (privdata->hw_init(pdev, cs, cs->io_base))
		goto Failure;

	/* Acquire shared access to the IRQ Channel. */
	if (request_irq(pdev->irq, irq_handler, IRQF_SHARED, "myrs", cs) < 0) {
		dev_err(&pdev->dev,
			"Unable to acquire IRQ Channel %d\n", pdev->irq);
		goto Failure;
	}
	cs->irq = pdev->irq;
	return cs;

Failure:
	dev_err(&pdev->dev,
		"Failed to initialize Controller\n");
	myrs_cleanup(cs);
	return NULL;
}