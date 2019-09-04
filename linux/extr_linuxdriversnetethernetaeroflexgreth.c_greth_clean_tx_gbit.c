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
typedef  size_t u16 ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bytes; } ;
struct net_device {TYPE_2__ stats; } ;
struct greth_private {size_t tx_last; size_t tx_next; int /*<<< orphan*/  dev; struct greth_bd* tx_bd_base; struct sk_buff** tx_skbuff; TYPE_1__* regs; } ;
struct greth_bd {int /*<<< orphan*/  addr; int /*<<< orphan*/  stat; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_6__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int GRETH_BD_EN ; 
 int GRETH_INT_TE ; 
 int GRETH_INT_TX ; 
 int /*<<< orphan*/  GRETH_REGSAVE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 size_t NEXT_TX (size_t) ; 
 int SKIP_TX (size_t,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ greth_num_free_bds (size_t,size_t) ; 
 int greth_read_bd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  greth_update_tx_stats (struct net_device*,int) ; 
 int /*<<< orphan*/  mb () ; 
 struct greth_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void greth_clean_tx_gbit(struct net_device *dev)
{
	struct greth_private *greth;
	struct greth_bd *bdp, *bdp_last_frag;
	struct sk_buff *skb = NULL;
	u32 stat;
	int nr_frags, i;
	u16 tx_last;

	greth = netdev_priv(dev);
	tx_last = greth->tx_last;

	while (tx_last != greth->tx_next) {

		skb = greth->tx_skbuff[tx_last];

		nr_frags = skb_shinfo(skb)->nr_frags;

		/* We only clean fully completed SKBs */
		bdp_last_frag = greth->tx_bd_base + SKIP_TX(tx_last, nr_frags);

		GRETH_REGSAVE(greth->regs->status, GRETH_INT_TE | GRETH_INT_TX);
		mb();
		stat = greth_read_bd(&bdp_last_frag->stat);

		if (stat & GRETH_BD_EN)
			break;

		greth->tx_skbuff[tx_last] = NULL;

		greth_update_tx_stats(dev, stat);
		dev->stats.tx_bytes += skb->len;

		bdp = greth->tx_bd_base + tx_last;

		tx_last = NEXT_TX(tx_last);

		dma_unmap_single(greth->dev,
				 greth_read_bd(&bdp->addr),
				 skb_headlen(skb),
				 DMA_TO_DEVICE);

		for (i = 0; i < nr_frags; i++) {
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
			bdp = greth->tx_bd_base + tx_last;

			dma_unmap_page(greth->dev,
				       greth_read_bd(&bdp->addr),
				       skb_frag_size(frag),
				       DMA_TO_DEVICE);

			tx_last = NEXT_TX(tx_last);
		}
		dev_kfree_skb(skb);
	}
	if (skb) { /* skb is set only if the above while loop was entered */
		wmb();
		greth->tx_last = tx_last;

		if (netif_queue_stopped(dev) &&
		    (greth_num_free_bds(tx_last, greth->tx_next) >
		    (MAX_SKB_FRAGS+1)))
			netif_wake_queue(dev);
	}
}