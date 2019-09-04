#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ dch; int /*<<< orphan*/  (* release ) (TYPE_2__*) ;} ;
struct fritzcard {int /*<<< orphan*/  list; int /*<<< orphan*/  pdev; int /*<<< orphan*/  addr; TYPE_2__ isac; int /*<<< orphan*/ * bch; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVM_cnt ; 
 int /*<<< orphan*/  ISDN_P_NONE ; 
 int /*<<< orphan*/  card_lock ; 
 int /*<<< orphan*/  disable_hwirq (struct fritzcard*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fritzcard*) ; 
 int /*<<< orphan*/  kfree (struct fritzcard*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_freebchannel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modehdlc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
release_card(struct fritzcard *card)
{
	u_long flags;

	disable_hwirq(card);
	spin_lock_irqsave(&card->lock, flags);
	modehdlc(&card->bch[0], ISDN_P_NONE);
	modehdlc(&card->bch[1], ISDN_P_NONE);
	spin_unlock_irqrestore(&card->lock, flags);
	card->isac.release(&card->isac);
	free_irq(card->irq, card);
	mISDN_freebchannel(&card->bch[1]);
	mISDN_freebchannel(&card->bch[0]);
	mISDN_unregister_device(&card->isac.dch.dev);
	release_region(card->addr, 32);
	pci_disable_device(card->pdev);
	pci_set_drvdata(card->pdev, NULL);
	write_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&card_lock, flags);
	kfree(card);
	AVM_cnt--;
}