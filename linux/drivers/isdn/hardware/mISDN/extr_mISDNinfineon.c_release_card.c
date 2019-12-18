#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {TYPE_1__ dch; int /*<<< orphan*/  (* release ) (TYPE_4__*) ;} ;
struct TYPE_6__ {TYPE_4__ isac; } ;
struct inf_hw {int /*<<< orphan*/  pdev; struct inf_hw** sc; TYPE_3__* ci; int /*<<< orphan*/  list; TYPE_2__ ipac; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int typ; } ;

/* Variables and functions */
#define  INF_SCT_1 131 
#define  INF_SCT_2 130 
#define  INF_SCT_3 129 
#define  INF_SCT_4 128 
 int /*<<< orphan*/  card_lock ; 
 int /*<<< orphan*/  disable_hwirq (struct inf_hw*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct inf_hw*) ; 
 int /*<<< orphan*/  inf_cnt ; 
 int /*<<< orphan*/  kfree (struct inf_hw*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_io (struct inf_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
release_card(struct inf_hw *card) {
	ulong	flags;
	int	i;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	spin_unlock_irqrestore(&card->lock, flags);
	card->ipac.isac.release(&card->ipac.isac);
	free_irq(card->irq, card);
	mISDN_unregister_device(&card->ipac.isac.dch.dev);
	release_io(card);
	write_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&card_lock, flags);
	switch (card->ci->typ) {
	case INF_SCT_2:
	case INF_SCT_3:
	case INF_SCT_4:
		break;
	case INF_SCT_1:
		for (i = 0; i < 3; i++) {
			if (card->sc[i])
				release_card(card->sc[i]);
			card->sc[i] = NULL;
		}
		/* fall through */
	default:
		pci_disable_device(card->pdev);
		pci_set_drvdata(card->pdev, NULL);
		break;
	}
	kfree(card);
	inf_cnt--;
}