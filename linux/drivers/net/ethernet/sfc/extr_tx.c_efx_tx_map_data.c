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
struct sk_buff {unsigned int data; } ;
struct efx_tx_queue {int /*<<< orphan*/  tso_long_headers; struct efx_nic* efx; } ;
struct efx_tx_buffer {unsigned short flags; size_t unmap_len; size_t dma_offset; size_t dma_addr; struct sk_buff* skb; } ;
struct efx_nic {TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  size_t dma_addr_t ;
struct TYPE_6__ {unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_5__ {unsigned int doff; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned short EFX_TX_BUF_CONT ; 
 unsigned short EFX_TX_BUF_MAP_SINGLE ; 
 unsigned short EFX_TX_BUF_SKB ; 
 int EIO ; 
 size_t dma_map_single (struct device*,unsigned int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,size_t) ; 
 struct efx_tx_buffer* efx_tx_map_chunk (struct efx_tx_queue*,size_t,size_t) ; 
 size_t skb_frag_dma_map (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t skb_frag_size (int /*<<< orphan*/ *) ; 
 size_t skb_headlen (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_transport_header (struct sk_buff*) ; 
 TYPE_2__* tcp_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_tx_map_data(struct efx_tx_queue *tx_queue, struct sk_buff *skb,
			   unsigned int segment_count)
{
	struct efx_nic *efx = tx_queue->efx;
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
	dma_flags = EFX_TX_BUF_MAP_SINGLE;
	unmap_len = len;
	unmap_addr = dma_addr;

	if (unlikely(dma_mapping_error(dma_dev, dma_addr)))
		return -EIO;

	if (segment_count) {
		/* For TSO we need to put the header in to a separate
		 * descriptor. Map this separately if necessary.
		 */
		size_t header_len = skb_transport_header(skb) - skb->data +
				(tcp_hdr(skb)->doff << 2u);

		if (header_len != len) {
			tx_queue->tso_long_headers++;
			efx_tx_map_chunk(tx_queue, dma_addr, header_len);
			len -= header_len;
			dma_addr += header_len;
		}
	}

	/* Add descriptors for each fragment. */
	do {
		struct efx_tx_buffer *buffer;
		skb_frag_t *fragment;

		buffer = efx_tx_map_chunk(tx_queue, dma_addr, len);

		/* The final descriptor for a fragment is responsible for
		 * unmapping the whole fragment.
		 */
		buffer->flags = EFX_TX_BUF_CONT | dma_flags;
		buffer->unmap_len = unmap_len;
		buffer->dma_offset = buffer->dma_addr - unmap_addr;

		if (frag_index >= nr_frags) {
			/* Store SKB details with the final buffer for
			 * the completion.
			 */
			buffer->skb = skb;
			buffer->flags = EFX_TX_BUF_SKB | dma_flags;
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