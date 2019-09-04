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
struct rsxx_cardinfo {int n_targets; int halt; int /*<<< orphan*/  disk_id; int /*<<< orphan*/  regmap; int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  event_work; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  CR_INTR_ALL ; 
 int /*<<< orphan*/  CR_INTR_DMA (int) ; 
 int /*<<< orphan*/  CR_INTR_EVENT ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int card_shutdown (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  force_legacy ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct rsxx_cardinfo* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  rsxx_creg_destroy (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_destroy_dev (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_detach_dev (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_disable_ier_and_isr (struct rsxx_cardinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsxx_disk_ida ; 
 int /*<<< orphan*/  rsxx_dma_destroy (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rsxx_pci_remove(struct pci_dev *dev)
{
	struct rsxx_cardinfo *card = pci_get_drvdata(dev);
	unsigned long flags;
	int st;
	int i;

	if (!card)
		return;

	dev_info(CARD_TO_DEV(card),
		"Removing PCI-Flash SSD.\n");

	rsxx_detach_dev(card);

	for (i = 0; i < card->n_targets; i++) {
		spin_lock_irqsave(&card->irq_lock, flags);
		rsxx_disable_ier_and_isr(card, CR_INTR_DMA(i));
		spin_unlock_irqrestore(&card->irq_lock, flags);
	}

	st = card_shutdown(card);
	if (st)
		dev_crit(CARD_TO_DEV(card), "Shutdown failed!\n");

	/* Sync outstanding event handlers. */
	spin_lock_irqsave(&card->irq_lock, flags);
	rsxx_disable_ier_and_isr(card, CR_INTR_EVENT);
	spin_unlock_irqrestore(&card->irq_lock, flags);

	cancel_work_sync(&card->event_work);

	rsxx_destroy_dev(card);
	rsxx_dma_destroy(card);

	spin_lock_irqsave(&card->irq_lock, flags);
	rsxx_disable_ier_and_isr(card, CR_INTR_ALL);
	spin_unlock_irqrestore(&card->irq_lock, flags);

	/* Prevent work_structs from re-queuing themselves. */
	card->halt = 1;

	debugfs_remove_recursive(card->debugfs_dir);

	free_irq(dev->irq, card);

	if (!force_legacy)
		pci_disable_msi(dev);

	rsxx_creg_destroy(card);

	pci_iounmap(dev, card->regmap);

	pci_disable_device(dev);
	pci_release_regions(dev);

	ida_free(&rsxx_disk_ida, card->disk_id);
	kfree(card);
}