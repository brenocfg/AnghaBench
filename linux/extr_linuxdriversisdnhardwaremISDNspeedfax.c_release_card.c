#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__ dch; int /*<<< orphan*/  (* release ) (TYPE_3__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (TYPE_2__*) ;} ;
struct sfax_hw {int /*<<< orphan*/  list; int /*<<< orphan*/  pdev; int /*<<< orphan*/  cfg; TYPE_3__ isac; TYPE_2__ isar; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  card_lock ; 
 int /*<<< orphan*/  disable_hwirq (struct sfax_hw*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sfax_hw*) ; 
 int /*<<< orphan*/  kfree (struct sfax_hw*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sfax_cnt ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
release_card(struct sfax_hw *card) {
	u_long	flags;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	spin_unlock_irqrestore(&card->lock, flags);
	card->isac.release(&card->isac);
	free_irq(card->irq, card);
	card->isar.release(&card->isar);
	mISDN_unregister_device(&card->isac.dch.dev);
	release_region(card->cfg, 256);
	pci_disable_device(card->pdev);
	pci_set_drvdata(card->pdev, NULL);
	write_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&card_lock, flags);
	kfree(card);
	sfax_cnt--;
}