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
struct r592_device {int /*<<< orphan*/  dummy_dma_page_physical_address; scalar_t__ dummy_dma_page; int /*<<< orphan*/  host; int /*<<< orphan*/  mmio; int /*<<< orphan*/  irq; TYPE_1__* req; int /*<<< orphan*/  io_thread; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct r592_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memstick_free_host (int /*<<< orphan*/ ) ; 
 int memstick_next_req (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  memstick_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct r592_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  r592_enable_device (struct r592_device*,int) ; 

__attribute__((used)) static void r592_remove(struct pci_dev *pdev)
{
	int error = 0;
	struct r592_device *dev = pci_get_drvdata(pdev);

	/* Stop the processing thread.
	That ensures that we won't take any more requests */
	kthread_stop(dev->io_thread);

	r592_enable_device(dev, false);

	while (!error && dev->req) {
		dev->req->error = -ETIME;
		error = memstick_next_req(dev->host, &dev->req);
	}
	memstick_remove_host(dev->host);

	free_irq(dev->irq, dev);
	iounmap(dev->mmio);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	memstick_free_host(dev->host);

	if (dev->dummy_dma_page)
		dma_free_coherent(&pdev->dev, PAGE_SIZE, dev->dummy_dma_page,
			dev->dummy_dma_page_physical_address);
}