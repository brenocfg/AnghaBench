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
struct sk_buff {scalar_t__ data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ixgb_desc_ring {unsigned int next_to_use; unsigned int count; struct ixgb_buffer* buffer_info; } ;
struct ixgb_buffer {unsigned int length; scalar_t__ dma; int mapped_as_page; unsigned int next_to_watch; struct sk_buff* skb; void* time_stamp; } ;
struct ixgb_adapter {struct pci_dev* pdev; struct ixgb_desc_ring tx_ring; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {unsigned int gso_size; unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IXGB_MAX_DATA_PER_TXD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ixgb_unmap_and_free_tx_resource (struct ixgb_adapter*,struct ixgb_buffer*) ; 
 void* jiffies ; 
 unsigned int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (int /*<<< orphan*/  const*) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ixgb_tx_map(struct ixgb_adapter *adapter, struct sk_buff *skb,
	    unsigned int first)
{
	struct ixgb_desc_ring *tx_ring = &adapter->tx_ring;
	struct pci_dev *pdev = adapter->pdev;
	struct ixgb_buffer *buffer_info;
	int len = skb_headlen(skb);
	unsigned int offset = 0, size, count = 0, i;
	unsigned int mss = skb_shinfo(skb)->gso_size;
	unsigned int nr_frags = skb_shinfo(skb)->nr_frags;
	unsigned int f;

	i = tx_ring->next_to_use;

	while (len) {
		buffer_info = &tx_ring->buffer_info[i];
		size = min(len, IXGB_MAX_DATA_PER_TXD);
		/* Workaround for premature desc write-backs
		 * in TSO mode.  Append 4-byte sentinel desc */
		if (unlikely(mss && !nr_frags && size == len && size > 8))
			size -= 4;

		buffer_info->length = size;
		WARN_ON(buffer_info->dma != 0);
		buffer_info->time_stamp = jiffies;
		buffer_info->mapped_as_page = false;
		buffer_info->dma = dma_map_single(&pdev->dev,
						  skb->data + offset,
						  size, DMA_TO_DEVICE);
		if (dma_mapping_error(&pdev->dev, buffer_info->dma))
			goto dma_error;
		buffer_info->next_to_watch = 0;

		len -= size;
		offset += size;
		count++;
		if (len) {
			i++;
			if (i == tx_ring->count)
				i = 0;
		}
	}

	for (f = 0; f < nr_frags; f++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[f];
		len = skb_frag_size(frag);
		offset = 0;

		while (len) {
			i++;
			if (i == tx_ring->count)
				i = 0;

			buffer_info = &tx_ring->buffer_info[i];
			size = min(len, IXGB_MAX_DATA_PER_TXD);

			/* Workaround for premature desc write-backs
			 * in TSO mode.  Append 4-byte sentinel desc */
			if (unlikely(mss && (f == (nr_frags - 1))
				     && size == len && size > 8))
				size -= 4;

			buffer_info->length = size;
			buffer_info->time_stamp = jiffies;
			buffer_info->mapped_as_page = true;
			buffer_info->dma =
				skb_frag_dma_map(&pdev->dev, frag, offset, size,
						 DMA_TO_DEVICE);
			if (dma_mapping_error(&pdev->dev, buffer_info->dma))
				goto dma_error;
			buffer_info->next_to_watch = 0;

			len -= size;
			offset += size;
			count++;
		}
	}
	tx_ring->buffer_info[i].skb = skb;
	tx_ring->buffer_info[first].next_to_watch = i;

	return count;

dma_error:
	dev_err(&pdev->dev, "TX DMA map failed\n");
	buffer_info->dma = 0;
	if (count)
		count--;

	while (count--) {
		if (i==0)
			i += tx_ring->count;
		i--;
		buffer_info = &tx_ring->buffer_info[i];
		ixgb_unmap_and_free_tx_resource(adapter, buffer_info);
	}

	return 0;
}