#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_6__ {scalar_t__ class; } ;
struct TYPE_10__ {TYPE_1__ dev; } ;
struct TYPE_7__ {TYPE_5__ dev; } ;
struct TYPE_8__ {TYPE_2__ dch; int /*<<< orphan*/  (* release ) (TYPE_3__*) ;} ;
struct tiger_hw {scalar_t__ irq; int /*<<< orphan*/  pdev; int /*<<< orphan*/  list; int /*<<< orphan*/  dma; scalar_t__ dma_p; TYPE_4__* bc; TYPE_3__ isac; scalar_t__ base_s; int /*<<< orphan*/  base; int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {struct tiger_hw* hrbuf; struct tiger_hw* hsbuf; int /*<<< orphan*/  bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_P_NONE ; 
 int /*<<< orphan*/  NJ_DMA_SIZE ; 
 int /*<<< orphan*/  card_lock ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct tiger_hw*) ; 
 int /*<<< orphan*/  kfree (struct tiger_hw*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_freebchannel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_unregister_device (TYPE_5__*) ; 
 int /*<<< orphan*/  mode_tiger (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nj_disable_hwirq (struct tiger_hw*) ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nj_release(struct tiger_hw *card)
{
	u_long flags;
	int i;

	if (card->base_s) {
		spin_lock_irqsave(&card->lock, flags);
		nj_disable_hwirq(card);
		mode_tiger(&card->bc[0], ISDN_P_NONE);
		mode_tiger(&card->bc[1], ISDN_P_NONE);
		card->isac.release(&card->isac);
		spin_unlock_irqrestore(&card->lock, flags);
		release_region(card->base, card->base_s);
		card->base_s = 0;
	}
	if (card->irq > 0)
		free_irq(card->irq, card);
	if (card->isac.dch.dev.dev.class)
		mISDN_unregister_device(&card->isac.dch.dev);

	for (i = 0; i < 2; i++) {
		mISDN_freebchannel(&card->bc[i].bch);
		kfree(card->bc[i].hsbuf);
		kfree(card->bc[i].hrbuf);
	}
	if (card->dma_p)
		pci_free_consistent(card->pdev, NJ_DMA_SIZE,
				    card->dma_p, card->dma);
	write_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&card_lock, flags);
	pci_clear_master(card->pdev);
	pci_disable_device(card->pdev);
	pci_set_drvdata(card->pdev, NULL);
	kfree(card);
}