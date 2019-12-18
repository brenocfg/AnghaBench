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
typedef  int u32 ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {TYPE_2__ stats; } ;
struct happy_meal_txd {int /*<<< orphan*/  tx_flags; int /*<<< orphan*/  tx_addr; } ;
struct happy_meal {int tx_old; int tx_new; int /*<<< orphan*/  dma_dev; struct sk_buff** tx_skbs; struct net_device* dev; TYPE_1__* happy_block; } ;
struct TYPE_6__ {int nr_frags; } ;
struct TYPE_4__ {struct happy_meal_txd* happy_meal_txd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int NEXT_TX (int) ; 
 int /*<<< orphan*/  TXD (char*) ; 
 int TXFLAG_OWN ; 
 int TXFLAG_SIZE ; 
 scalar_t__ TX_BUFFS_AVAIL (struct happy_meal*) ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int hme_read_desc32 (struct happy_meal*,int /*<<< orphan*/ *) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void happy_meal_tx(struct happy_meal *hp)
{
	struct happy_meal_txd *txbase = &hp->happy_block->happy_meal_txd[0];
	struct happy_meal_txd *this;
	struct net_device *dev = hp->dev;
	int elem;

	elem = hp->tx_old;
	TXD(("TX<"));
	while (elem != hp->tx_new) {
		struct sk_buff *skb;
		u32 flags, dma_addr, dma_len;
		int frag;

		TXD(("[%d]", elem));
		this = &txbase[elem];
		flags = hme_read_desc32(hp, &this->tx_flags);
		if (flags & TXFLAG_OWN)
			break;
		skb = hp->tx_skbs[elem];
		if (skb_shinfo(skb)->nr_frags) {
			int last;

			last = elem + skb_shinfo(skb)->nr_frags;
			last &= (TX_RING_SIZE - 1);
			flags = hme_read_desc32(hp, &txbase[last].tx_flags);
			if (flags & TXFLAG_OWN)
				break;
		}
		hp->tx_skbs[elem] = NULL;
		dev->stats.tx_bytes += skb->len;

		for (frag = 0; frag <= skb_shinfo(skb)->nr_frags; frag++) {
			dma_addr = hme_read_desc32(hp, &this->tx_addr);
			dma_len = hme_read_desc32(hp, &this->tx_flags);

			dma_len &= TXFLAG_SIZE;
			if (!frag)
				dma_unmap_single(hp->dma_dev, dma_addr, dma_len, DMA_TO_DEVICE);
			else
				dma_unmap_page(hp->dma_dev, dma_addr, dma_len, DMA_TO_DEVICE);

			elem = NEXT_TX(elem);
			this = &txbase[elem];
		}

		dev_consume_skb_irq(skb);
		dev->stats.tx_packets++;
	}
	hp->tx_old = elem;
	TXD((">"));

	if (netif_queue_stopped(dev) &&
	    TX_BUFFS_AVAIL(hp) > (MAX_SKB_FRAGS + 1))
		netif_wake_queue(dev);
}