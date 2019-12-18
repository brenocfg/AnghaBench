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
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  l1; } ;
struct w6692_hw {int fmask; scalar_t__ subtype; int xdata; int /*<<< orphan*/  pdev; int /*<<< orphan*/  list; TYPE_2__ dch; TYPE_1__* bc; int /*<<< orphan*/  addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_CHANNEL ; 
 int /*<<< orphan*/  ISDN_P_NONE ; 
 scalar_t__ W6692_USR ; 
 int /*<<< orphan*/  W_XDATA ; 
 int /*<<< orphan*/  WriteW6692 (struct w6692_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  card_lock ; 
 int /*<<< orphan*/  disable_hwirq (struct w6692_hw*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct w6692_hw*) ; 
 int /*<<< orphan*/  kfree (struct w6692_hw*) ; 
 int /*<<< orphan*/  l1_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int led ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_freebchannel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_freedchannel (TYPE_2__*) ; 
 int /*<<< orphan*/  mISDN_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w6692_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
release_card(struct w6692_hw *card)
{
	u_long	flags;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	w6692_mode(&card->bc[0], ISDN_P_NONE);
	w6692_mode(&card->bc[1], ISDN_P_NONE);
	if ((card->fmask & led) || card->subtype == W6692_USR) {
		card->xdata |= 0x04;	/*  LED OFF */
		WriteW6692(card, W_XDATA, card->xdata);
	}
	spin_unlock_irqrestore(&card->lock, flags);
	free_irq(card->irq, card);
	l1_event(card->dch.l1, CLOSE_CHANNEL);
	mISDN_unregister_device(&card->dch.dev);
	release_region(card->addr, 256);
	mISDN_freebchannel(&card->bc[1].bch);
	mISDN_freebchannel(&card->bc[0].bch);
	mISDN_freedchannel(&card->dch);
	write_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&card_lock, flags);
	pci_disable_device(card->pdev);
	pci_set_drvdata(card->pdev, NULL);
	kfree(card);
}