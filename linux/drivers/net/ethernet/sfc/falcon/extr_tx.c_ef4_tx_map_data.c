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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct ef4_tx_queue {struct ef4_nic* efx; } ;
struct ef4_tx_buffer {unsigned short flags; size_t unmap_len; struct sk_buff* skb; scalar_t__ dma_addr; scalar_t__ dma_offset; } ;
struct ef4_nic {TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned short EF4_TX_BUF_CONT ; 
 unsigned short EF4_TX_BUF_MAP_SINGLE ; 
 unsigned short EF4_TX_BUF_SKB ; 
 int EIO ; 
 scalar_t__ dma_map_single (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,scalar_t__) ; 
 struct ef4_tx_buffer* ef4_tx_map_chunk (struct ef4_tx_queue*,scalar_t__,size_t) ; 
 scalar_t__ skb_frag_dma_map (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t skb_frag_size (int /*<<< orphan*/ *) ; 
 size_t skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ef4_tx_map_data(struct ef4_tx_queue *tx_queue, struct sk_buff *skb)
{
	struct ef4_nic *efx = tx_queue->efx;
	struct device *dma_dev = &efx->pci_dev->dev;
	unsigned int frag_index, nr_frags;
	dma_addr_t dma_addr, unmap_addr;
	unsigned short dma_flags;
	size_t len, unmap_len;

	nr_frags = skb_shinfo(skb)->nr_frags;
	frag_index = 0;

	/* Map header data. */
	len = skb_headlen(skb);
	dma_addr = dma_map_single(dma_dev, skb->data, len, DMA_TO_DEVICE);
	dma_flags = EF4_TX_BUF_MAP_SINGLE;
	unmap_len = len;
	unmap_addr = dma_addr;

	if (unlikely(dma_mapping_error(dma_dev, dma_addr)))
		return -EIO;

	/* Add descriptors for each fragment. */
	do {
		struct ef4_tx_buffer *buffer;
		skb_frag_t *fragment;

		buffer = ef4_tx_map_chunk(tx_queue, dma_addr, len);

		/* The final descriptor for a fragment is responsible for
		 * unmapping the whole fragment.
		 */
		buffer->flags = EF4_TX_BUF_CONT | dma_flags;
		buffer->unmap_len = unmap_len;
		buffer->dma_offset = buffer->dma_addr - unmap_addr;

		if (frag_index >= nr_frags) {
			/* Store SKB details with the final buffer for
			 * the completion.
			 */
			buffer->skb = skb;
			buffer->flags = EF4_TX_BUF_SKB | dma_flags;
			return 0;
		}

		/* Move on to the next fragment. */
		fragment = &skb_shinfo(skb)->frags[frag_index++];
		len = skb_frag_size(fragment);
		dma_addr = skb_frag_dma_map(dma_dev, fragment,
				0, len, DMA_TO_DEVICE);
		dma_flags = 0;
		unmap_len = len;
		unmap_addr = dma_addr;

		if (unlikely(dma_mapping_error(dma_dev, dma_addr)))
			return -EIO;
	} while (1);
}