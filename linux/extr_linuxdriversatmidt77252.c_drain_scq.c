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
struct vc_map {struct scq_info* scq; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct scq_info {int /*<<< orphan*/  skblock; int /*<<< orphan*/  pending; int /*<<< orphan*/  used; int /*<<< orphan*/  transmit; int /*<<< orphan*/  next; } ;
struct idt77252_dev {TYPE_1__* pcidev; int /*<<< orphan*/  name; } ;
struct atm_vcc {TYPE_2__* stats; int /*<<< orphan*/  (* pop ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct TYPE_6__ {struct atm_vcc* vcc; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_3__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IDT77252_PRV_PADDR (struct sk_buff*) ; 
 int /*<<< orphan*/  TXPRINTK (char*,int /*<<< orphan*/ ,struct sk_buff*,...) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ push_on_scq (struct idt77252_dev*,struct vc_map*,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static void
drain_scq(struct idt77252_dev *card, struct vc_map *vc)
{
	struct scq_info *scq = vc->scq;
	struct sk_buff *skb;
	struct atm_vcc *vcc;

	TXPRINTK("%s: SCQ (before drain %2d) next = 0x%p.\n",
		 card->name, atomic_read(&scq->used), scq->next);

	skb = skb_dequeue(&scq->transmit);
	if (skb) {
		TXPRINTK("%s: freeing skb at %p.\n", card->name, skb);

		dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				 skb->len, DMA_TO_DEVICE);

		vcc = ATM_SKB(skb)->vcc;

		if (vcc->pop)
			vcc->pop(vcc, skb);
		else
			dev_kfree_skb(skb);

		atomic_inc(&vcc->stats->tx);
	}

	atomic_dec(&scq->used);

	spin_lock(&scq->skblock);
	while ((skb = skb_dequeue(&scq->pending))) {
		if (push_on_scq(card, vc, skb)) {
			skb_queue_head(&vc->scq->pending, skb);
			break;
		}
	}
	spin_unlock(&scq->skblock);
}