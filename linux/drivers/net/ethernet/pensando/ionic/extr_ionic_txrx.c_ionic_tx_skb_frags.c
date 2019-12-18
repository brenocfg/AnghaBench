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
typedef  scalar_t__ u16 ;
struct sk_buff {unsigned int len; } ;
struct ionic_txq_sg_elem {int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct ionic_txq_sg_desc {struct ionic_txq_sg_elem* elems; } ;
struct ionic_tx_stats {int /*<<< orphan*/  frags; } ;
struct ionic_queue {TYPE_3__* lif; TYPE_1__* head; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/ * frags; } ;
struct TYPE_7__ {TYPE_2__* ionic; } ;
struct TYPE_6__ {struct device* dev; } ;
struct TYPE_5__ {struct ionic_txq_sg_desc* sg_desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_tx_map_frag (struct ionic_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ionic_tx_stats* q_to_tx_stats (struct ionic_queue*) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int ionic_tx_skb_frags(struct ionic_queue *q, struct sk_buff *skb)
{
	struct ionic_txq_sg_desc *sg_desc = q->head->sg_desc;
	unsigned int len_left = skb->len - skb_headlen(skb);
	struct ionic_txq_sg_elem *elem = sg_desc->elems;
	struct ionic_tx_stats *stats = q_to_tx_stats(q);
	struct device *dev = q->lif->ionic->dev;
	dma_addr_t dma_addr;
	skb_frag_t *frag;
	u16 len;

	for (frag = skb_shinfo(skb)->frags; len_left; frag++, elem++) {
		len = skb_frag_size(frag);
		elem->len = cpu_to_le16(len);
		dma_addr = ionic_tx_map_frag(q, frag, 0, len);
		if (dma_mapping_error(dev, dma_addr))
			return -ENOMEM;
		elem->addr = cpu_to_le64(dma_addr);
		len_left -= len;
		stats->frags++;
	}

	return 0;
}