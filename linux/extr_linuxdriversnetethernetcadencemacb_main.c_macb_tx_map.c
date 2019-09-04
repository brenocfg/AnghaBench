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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ data; } ;
struct macb_tx_skb {unsigned int size; int mapped_as_page; void* mapping; struct sk_buff* skb; } ;
struct macb_queue {unsigned int tx_head; struct macb_tx_skb* tx_skb; } ;
struct macb_dma_desc {scalar_t__ ctrl; } ;
struct macb {int tx_ring_size; TYPE_3__* dev; TYPE_1__* pdev; int /*<<< orphan*/  max_tx_length; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  void* dma_addr_t ;
struct TYPE_8__ {scalar_t__ protocol; } ;
struct TYPE_7__ {int features; } ;
struct TYPE_6__ {unsigned int nr_frags; unsigned int gso_size; int /*<<< orphan*/ * frags; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned int ETH_FCS_LEN ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ MACB_BF (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ MACB_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ MACB_LSO_TSO_ENABLE ; 
 scalar_t__ MACB_LSO_UFO_ENABLE ; 
 int /*<<< orphan*/  MSS_MFS ; 
 int NETIF_F_HW_CSUM ; 
 int /*<<< orphan*/  TX_LAST ; 
 int /*<<< orphan*/  TX_LSO ; 
 int /*<<< orphan*/  TX_NOCRC ; 
 int /*<<< orphan*/  TX_TCP_SEQ_SRC ; 
 int /*<<< orphan*/  TX_USED ; 
 int /*<<< orphan*/  TX_WRAP ; 
 void* dma_map_single (int /*<<< orphan*/ *,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  macb_set_addr (struct macb*,struct macb_dma_desc*,void*) ; 
 struct macb_dma_desc* macb_tx_desc (struct macb_queue*,unsigned int) ; 
 unsigned int macb_tx_ring_wrap (struct macb*,unsigned int) ; 
 struct macb_tx_skb* macb_tx_skb (struct macb_queue*,unsigned int) ; 
 int /*<<< orphan*/  macb_tx_unmap (struct macb*,struct macb_tx_skb*) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (TYPE_3__*,char*) ; 
 void* skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/  const*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static unsigned int macb_tx_map(struct macb *bp,
				struct macb_queue *queue,
				struct sk_buff *skb,
				unsigned int hdrlen)
{
	dma_addr_t mapping;
	unsigned int len, entry, i, tx_head = queue->tx_head;
	struct macb_tx_skb *tx_skb = NULL;
	struct macb_dma_desc *desc;
	unsigned int offset, size, count = 0;
	unsigned int f, nr_frags = skb_shinfo(skb)->nr_frags;
	unsigned int eof = 1, mss_mfs = 0;
	u32 ctrl, lso_ctrl = 0, seq_ctrl = 0;

	/* LSO */
	if (skb_shinfo(skb)->gso_size != 0) {
		if (ip_hdr(skb)->protocol == IPPROTO_UDP)
			/* UDP - UFO */
			lso_ctrl = MACB_LSO_UFO_ENABLE;
		else
			/* TCP - TSO */
			lso_ctrl = MACB_LSO_TSO_ENABLE;
	}

	/* First, map non-paged data */
	len = skb_headlen(skb);

	/* first buffer length */
	size = hdrlen;

	offset = 0;
	while (len) {
		entry = macb_tx_ring_wrap(bp, tx_head);
		tx_skb = &queue->tx_skb[entry];

		mapping = dma_map_single(&bp->pdev->dev,
					 skb->data + offset,
					 size, DMA_TO_DEVICE);
		if (dma_mapping_error(&bp->pdev->dev, mapping))
			goto dma_error;

		/* Save info to properly release resources */
		tx_skb->skb = NULL;
		tx_skb->mapping = mapping;
		tx_skb->size = size;
		tx_skb->mapped_as_page = false;

		len -= size;
		offset += size;
		count++;
		tx_head++;

		size = min(len, bp->max_tx_length);
	}

	/* Then, map paged data from fragments */
	for (f = 0; f < nr_frags; f++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		len = skb_frag_size(frag);
		offset = 0;
		while (len) {
			size = min(len, bp->max_tx_length);
			entry = macb_tx_ring_wrap(bp, tx_head);
			tx_skb = &queue->tx_skb[entry];

			mapping = skb_frag_dma_map(&bp->pdev->dev, frag,
						   offset, size, DMA_TO_DEVICE);
			if (dma_mapping_error(&bp->pdev->dev, mapping))
				goto dma_error;

			/* Save info to properly release resources */
			tx_skb->skb = NULL;
			tx_skb->mapping = mapping;
			tx_skb->size = size;
			tx_skb->mapped_as_page = true;

			len -= size;
			offset += size;
			count++;
			tx_head++;
		}
	}

	/* Should never happen */
	if (unlikely(!tx_skb)) {
		netdev_err(bp->dev, "BUG! empty skb!\n");
		return 0;
	}

	/* This is the last buffer of the frame: save socket buffer */
	tx_skb->skb = skb;

	/* Update TX ring: update buffer descriptors in reverse order
	 * to avoid race condition
	 */

	/* Set 'TX_USED' bit in buffer descriptor at tx_head position
	 * to set the end of TX queue
	 */
	i = tx_head;
	entry = macb_tx_ring_wrap(bp, i);
	ctrl = MACB_BIT(TX_USED);
	desc = macb_tx_desc(queue, entry);
	desc->ctrl = ctrl;

	if (lso_ctrl) {
		if (lso_ctrl == MACB_LSO_UFO_ENABLE)
			/* include header and FCS in value given to h/w */
			mss_mfs = skb_shinfo(skb)->gso_size +
					skb_transport_offset(skb) +
					ETH_FCS_LEN;
		else /* TSO */ {
			mss_mfs = skb_shinfo(skb)->gso_size;
			/* TCP Sequence Number Source Select
			 * can be set only for TSO
			 */
			seq_ctrl = 0;
		}
	}

	do {
		i--;
		entry = macb_tx_ring_wrap(bp, i);
		tx_skb = &queue->tx_skb[entry];
		desc = macb_tx_desc(queue, entry);

		ctrl = (u32)tx_skb->size;
		if (eof) {
			ctrl |= MACB_BIT(TX_LAST);
			eof = 0;
		}
		if (unlikely(entry == (bp->tx_ring_size - 1)))
			ctrl |= MACB_BIT(TX_WRAP);

		/* First descriptor is header descriptor */
		if (i == queue->tx_head) {
			ctrl |= MACB_BF(TX_LSO, lso_ctrl);
			ctrl |= MACB_BF(TX_TCP_SEQ_SRC, seq_ctrl);
			if ((bp->dev->features & NETIF_F_HW_CSUM) &&
			    skb->ip_summed != CHECKSUM_PARTIAL && !lso_ctrl)
				ctrl |= MACB_BIT(TX_NOCRC);
		} else
			/* Only set MSS/MFS on payload descriptors
			 * (second or later descriptor)
			 */
			ctrl |= MACB_BF(MSS_MFS, mss_mfs);

		/* Set TX buffer descriptor */
		macb_set_addr(bp, desc, tx_skb->mapping);
		/* desc->addr must be visible to hardware before clearing
		 * 'TX_USED' bit in desc->ctrl.
		 */
		wmb();
		desc->ctrl = ctrl;
	} while (i != queue->tx_head);

	queue->tx_head = tx_head;

	return count;

dma_error:
	netdev_err(bp->dev, "TX DMA map failed\n");

	for (i = queue->tx_head; i != tx_head; i++) {
		tx_skb = macb_tx_skb(queue, i);

		macb_tx_unmap(bp, tx_skb);
	}

	return 0;
}