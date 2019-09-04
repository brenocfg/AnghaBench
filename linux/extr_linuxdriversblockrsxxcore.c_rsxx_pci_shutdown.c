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
struct rsxx_cardinfo {int n_targets; int /*<<< orphan*/  irq_lock; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  CR_INTR_DMA (int) ; 
 int /*<<< orphan*/  card_shutdown (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct rsxx_cardinfo* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rsxx_detach_dev (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_disable_ier_and_isr (struct rsxx_cardinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rsxx_pci_shutdown(struct pci_dev *dev)
{
	struct rsxx_cardinfo *card = pci_get_drvdata(dev);
	unsigned long flags;
	int i;

	if (!card)
		return;

	dev_info(CARD_TO_DEV(card), "Shutting down PCI-Flash SSD.\n");

	rsxx_detach_dev(card);

	for (i = 0; i < card->n_targets; i++) {
		spin_lock_irqsave(&card->irq_lock, flags);
		rsxx_disable_ier_and_isr(card, CR_INTR_DMA(i));
		spin_unlock_irqrestore(&card->irq_lock, flags);
	}

	card_shutdown(card);
}