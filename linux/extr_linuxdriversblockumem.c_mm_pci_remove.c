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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct cardinfo {int /*<<< orphan*/  queue; TYPE_1__* mm_pages; int /*<<< orphan*/  dev; int /*<<< orphan*/  csr_remap; int /*<<< orphan*/  tasklet; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_dma; scalar_t__ desc; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cardinfo*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct cardinfo* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mm_pci_remove(struct pci_dev *dev)
{
	struct cardinfo *card = pci_get_drvdata(dev);

	tasklet_kill(&card->tasklet);
	free_irq(dev->irq, card);
	iounmap(card->csr_remap);

	if (card->mm_pages[0].desc)
		pci_free_consistent(card->dev, PAGE_SIZE*2,
				    card->mm_pages[0].desc,
				    card->mm_pages[0].page_dma);
	if (card->mm_pages[1].desc)
		pci_free_consistent(card->dev, PAGE_SIZE*2,
				    card->mm_pages[1].desc,
				    card->mm_pages[1].page_dma);
	blk_cleanup_queue(card->queue);

	pci_release_regions(dev);
	pci_disable_device(dev);
}