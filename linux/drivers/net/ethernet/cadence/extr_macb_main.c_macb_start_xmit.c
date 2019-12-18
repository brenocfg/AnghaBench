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
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  head; int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct macb_queue {int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_head; } ;
struct macb {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  max_tx_length; struct macb_queue* queues; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {scalar_t__ protocol; } ;
struct TYPE_3__ {scalar_t__ gso_size; unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int CIRC_SPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  TSTART ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ macb_clear_csum (struct sk_buff*) ; 
 scalar_t__ macb_pad_and_fcs (struct sk_buff**,struct net_device*) ; 
 int macb_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_tx_map (struct macb*,struct macb_queue*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct macb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_vdbg (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_subqueue (struct net_device*,size_t) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  skb_end_pointer (struct sk_buff*) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int tcp_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t macb_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	u16 queue_index = skb_get_queue_mapping(skb);
	struct macb *bp = netdev_priv(dev);
	struct macb_queue *queue = &bp->queues[queue_index];
	unsigned long flags;
	unsigned int desc_cnt, nr_frags, frag_size, f;
	unsigned int hdrlen;
	bool is_lso, is_udp = 0;
	netdev_tx_t ret = NETDEV_TX_OK;

	if (macb_clear_csum(skb)) {
		dev_kfree_skb_any(skb);
		return ret;
	}

	if (macb_pad_and_fcs(&skb, dev)) {
		dev_kfree_skb_any(skb);
		return ret;
	}

	is_lso = (skb_shinfo(skb)->gso_size != 0);

	if (is_lso) {
		is_udp = !!(ip_hdr(skb)->protocol == IPPROTO_UDP);

		/* length of headers */
		if (is_udp)
			/* only queue eth + ip headers separately for UDP */
			hdrlen = skb_transport_offset(skb);
		else
			hdrlen = skb_transport_offset(skb) + tcp_hdrlen(skb);
		if (skb_headlen(skb) < hdrlen) {
			netdev_err(bp->dev, "Error - LSO headers fragmented!!!\n");
			/* if this is required, would need to copy to single buffer */
			return NETDEV_TX_BUSY;
		}
	} else
		hdrlen = min(skb_headlen(skb), bp->max_tx_length);

#if defined(DEBUG) && defined(VERBOSE_DEBUG)
	netdev_vdbg(bp->dev,
		    "start_xmit: queue %hu len %u head %p data %p tail %p end %p\n",
		    queue_index, skb->len, skb->head, skb->data,
		    skb_tail_pointer(skb), skb_end_pointer(skb));
	print_hex_dump(KERN_DEBUG, "data: ", DUMP_PREFIX_OFFSET, 16, 1,
		       skb->data, 16, true);
#endif

	/* Count how many TX buffer descriptors are needed to send this
	 * socket buffer: skb fragments of jumbo frames may need to be
	 * split into many buffer descriptors.
	 */
	if (is_lso && (skb_headlen(skb) > hdrlen))
		/* extra header descriptor if also payload in first buffer */
		desc_cnt = DIV_ROUND_UP((skb_headlen(skb) - hdrlen), bp->max_tx_length) + 1;
	else
		desc_cnt = DIV_ROUND_UP(skb_headlen(skb), bp->max_tx_length);
	nr_frags = skb_shinfo(skb)->nr_frags;
	for (f = 0; f < nr_frags; f++) {
		frag_size = skb_frag_size(&skb_shinfo(skb)->frags[f]);
		desc_cnt += DIV_ROUND_UP(frag_size, bp->max_tx_length);
	}

	spin_lock_irqsave(&bp->lock, flags);

	/* This is a hard error, log it. */
	if (CIRC_SPACE(queue->tx_head, queue->tx_tail,
		       bp->tx_ring_size) < desc_cnt) {
		netif_stop_subqueue(dev, queue_index);
		spin_unlock_irqrestore(&bp->lock, flags);
		netdev_dbg(bp->dev, "tx_head = %u, tx_tail = %u\n",
			   queue->tx_head, queue->tx_tail);
		return NETDEV_TX_BUSY;
	}

	/* Map socket buffer for DMA transfer */
	if (!macb_tx_map(bp, queue, skb, hdrlen)) {
		dev_kfree_skb_any(skb);
		goto unlock;
	}

	/* Make newly initialized descriptor visible to hardware */
	wmb();
	skb_tx_timestamp(skb);

	macb_writel(bp, NCR, macb_readl(bp, NCR) | MACB_BIT(TSTART));

	if (CIRC_SPACE(queue->tx_head, queue->tx_tail, bp->tx_ring_size) < 1)
		netif_stop_subqueue(dev, queue_index);

unlock:
	spin_unlock_irqrestore(&bp->lock, flags);

	return ret;
}