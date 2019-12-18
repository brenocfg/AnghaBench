#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct b43_rxhdr_fw4 {int /*<<< orphan*/  frame_len; } ;
struct b43_dmaring {scalar_t__ rx_buffersize; scalar_t__ frameoffset; TYPE_1__* dev; struct b43_dma_ops* ops; } ;
struct b43_dmadesc_meta {int /*<<< orphan*/  dmaaddr; struct sk_buff* skb; } ;
struct b43_dmadesc_generic {int dummy; } ;
struct b43_dma_ops {struct b43_dmadesc_generic* (* idx2desc ) (struct b43_dmaring*,int,struct b43_dmadesc_meta**) ;} ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  b43_poison_rx_buffer (struct b43_dmaring*,struct sk_buff*) ; 
 int /*<<< orphan*/  b43_rx (TYPE_1__*,struct sk_buff*,struct b43_rxhdr_fw4*) ; 
 int b43_rx_buffer_is_poisoned (struct b43_dmaring*,struct sk_buff*) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int next_slot (struct b43_dmaring*,int) ; 
 int setup_rx_descbuffer (struct b43_dmaring*,struct b43_dmadesc_generic*,struct b43_dmadesc_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 struct b43_dmadesc_generic* stub1 (struct b43_dmaring*,int,struct b43_dmadesc_meta**) ; 
 struct b43_dmadesc_generic* stub2 (struct b43_dmaring*,int,struct b43_dmadesc_meta**) ; 
 int /*<<< orphan*/  sync_descbuffer_for_cpu (struct b43_dmaring*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sync_descbuffer_for_device (struct b43_dmaring*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmap_descbuffer (struct b43_dmaring*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_rx(struct b43_dmaring *ring, int *slot)
{
	const struct b43_dma_ops *ops = ring->ops;
	struct b43_dmadesc_generic *desc;
	struct b43_dmadesc_meta *meta;
	struct b43_rxhdr_fw4 *rxhdr;
	struct sk_buff *skb;
	u16 len;
	int err;
	dma_addr_t dmaaddr;

	desc = ops->idx2desc(ring, *slot, &meta);

	sync_descbuffer_for_cpu(ring, meta->dmaaddr, ring->rx_buffersize);
	skb = meta->skb;

	rxhdr = (struct b43_rxhdr_fw4 *)skb->data;
	len = le16_to_cpu(rxhdr->frame_len);
	if (len == 0) {
		int i = 0;

		do {
			udelay(2);
			barrier();
			len = le16_to_cpu(rxhdr->frame_len);
		} while (len == 0 && i++ < 5);
		if (unlikely(len == 0)) {
			dmaaddr = meta->dmaaddr;
			goto drop_recycle_buffer;
		}
	}
	if (unlikely(b43_rx_buffer_is_poisoned(ring, skb))) {
		/* Something went wrong with the DMA.
		 * The device did not touch the buffer and did not overwrite the poison. */
		b43dbg(ring->dev->wl, "DMA RX: Dropping poisoned buffer.\n");
		dmaaddr = meta->dmaaddr;
		goto drop_recycle_buffer;
	}
	if (unlikely(len + ring->frameoffset > ring->rx_buffersize)) {
		/* The data did not fit into one descriptor buffer
		 * and is split over multiple buffers.
		 * This should never happen, as we try to allocate buffers
		 * big enough. So simply ignore this packet.
		 */
		int cnt = 0;
		s32 tmp = len;

		while (1) {
			desc = ops->idx2desc(ring, *slot, &meta);
			/* recycle the descriptor buffer. */
			b43_poison_rx_buffer(ring, meta->skb);
			sync_descbuffer_for_device(ring, meta->dmaaddr,
						   ring->rx_buffersize);
			*slot = next_slot(ring, *slot);
			cnt++;
			tmp -= ring->rx_buffersize;
			if (tmp <= 0)
				break;
		}
		b43err(ring->dev->wl, "DMA RX buffer too small "
		       "(len: %u, buffer: %u, nr-dropped: %d)\n",
		       len, ring->rx_buffersize, cnt);
		goto drop;
	}

	dmaaddr = meta->dmaaddr;
	err = setup_rx_descbuffer(ring, desc, meta, GFP_ATOMIC);
	if (unlikely(err)) {
		b43dbg(ring->dev->wl, "DMA RX: setup_rx_descbuffer() failed\n");
		goto drop_recycle_buffer;
	}

	unmap_descbuffer(ring, dmaaddr, ring->rx_buffersize, 0);
	skb_put(skb, len + ring->frameoffset);
	skb_pull(skb, ring->frameoffset);

	b43_rx(ring->dev, skb, rxhdr);
drop:
	return;

drop_recycle_buffer:
	/* Poison and recycle the RX buffer. */
	b43_poison_rx_buffer(ring, skb);
	sync_descbuffer_for_device(ring, dmaaddr, ring->rx_buffersize);
}