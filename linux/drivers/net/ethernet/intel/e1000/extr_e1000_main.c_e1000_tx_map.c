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
struct sk_buff {unsigned int data; unsigned int len; int /*<<< orphan*/  data_len; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct e1000_tx_ring {unsigned int next_to_use; int last_tx_tso; unsigned int count; struct e1000_tx_buffer* buffer_info; } ;
struct e1000_tx_buffer {unsigned int length; int mapped_as_page; unsigned int next_to_watch; unsigned int segs; unsigned int bytecount; scalar_t__ dma; struct sk_buff* skb; void* time_stamp; } ;
struct e1000_hw {scalar_t__ bus_type; } ;
struct e1000_adapter {scalar_t__ pcix_82544; struct pci_dev* pdev; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {scalar_t__ gso_segs; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ e1000_bus_type_pcix ; 
 int /*<<< orphan*/  e1000_unmap_and_free_tx_resource (struct e1000_adapter*,struct e1000_tx_buffer*) ; 
 void* jiffies ; 
 unsigned int min (unsigned int,unsigned int) ; 
 scalar_t__ page_to_phys (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/  const*) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/  const*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int e1000_tx_map(struct e1000_adapter *adapter,
			struct e1000_tx_ring *tx_ring,
			struct sk_buff *skb, unsigned int first,
			unsigned int max_per_txd, unsigned int nr_frags,
			unsigned int mss)
{
	struct e1000_hw *hw = &adapter->hw;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_tx_buffer *buffer_info;
	unsigned int len = skb_headlen(skb);
	unsigned int offset = 0, size, count = 0, i;
	unsigned int f, bytecount, segs;

	i = tx_ring->next_to_use;

	while (len) {
		buffer_info = &tx_ring->buffer_info[i];
		size = min(len, max_per_txd);
		/* Workaround for Controller erratum --
		 * descriptor for non-tso packet in a linear SKB that follows a
		 * tso gets written back prematurely before the data is fully
		 * DMA'd to the controller
		 */
		if (!skb->data_len && tx_ring->last_tx_tso &&
		    !skb_is_gso(skb)) {
			tx_ring->last_tx_tso = false;
			size -= 4;
		}

		/* Workaround for premature desc write-backs
		 * in TSO mode.  Append 4-byte sentinel desc
		 */
		if (unlikely(mss && !nr_frags && size == len && size > 8))
			size -= 4;
		/* work-around for errata 10 and it applies
		 * to all controllers in PCI-X mode
		 * The fix is to make sure that the first descriptor of a
		 * packet is smaller than 2048 - 16 - 16 (or 2016) bytes
		 */
		if (unlikely((hw->bus_type == e1000_bus_type_pcix) &&
			     (size > 2015) && count == 0))
			size = 2015;

		/* Workaround for potential 82544 hang in PCI-X.  Avoid
		 * terminating buffers within evenly-aligned dwords.
		 */
		if (unlikely(adapter->pcix_82544 &&
		   !((unsigned long)(skb->data + offset + size - 1) & 4) &&
		   size > 4))
			size -= 4;

		buffer_info->length = size;
		/* set time_stamp *before* dma to help avoid a possible race */
		buffer_info->time_stamp = jiffies;
		buffer_info->mapped_as_page = false;
		buffer_info->dma = dma_map_single(&pdev->dev,
						  skb->data + offset,
						  size, DMA_TO_DEVICE);
		if (dma_mapping_error(&pdev->dev, buffer_info->dma))
			goto dma_error;
		buffer_info->next_to_watch = i;

		len -= size;
		offset += size;
		count++;
		if (len) {
			i++;
			if (unlikely(i == tx_ring->count))
				i = 0;
		}
	}

	for (f = 0; f < nr_frags; f++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		len = skb_frag_size(frag);
		offset = 0;

		while (len) {
			unsigned long bufend;
			i++;
			if (unlikely(i == tx_ring->count))
				i = 0;

			buffer_info = &tx_ring->buffer_info[i];
			size = min(len, max_per_txd);
			/* Workaround for premature desc write-backs
			 * in TSO mode.  Append 4-byte sentinel desc
			 */
			if (unlikely(mss && f == (nr_frags-1) &&
			    size == len && size > 8))
				size -= 4;
			/* Workaround for potential 82544 hang in PCI-X.
			 * Avoid terminating buffers within evenly-aligned
			 * dwords.
			 */
			bufend = (unsigned long)
				page_to_phys(skb_frag_page(frag));
			bufend += offset + size - 1;
			if (unlikely(adapter->pcix_82544 &&
				     !(bufend & 4) &&
				     size > 4))
				size -= 4;

			buffer_info->length = size;
			buffer_info->time_stamp = jiffies;
			buffer_info->mapped_as_page = true;
			buffer_info->dma = skb_frag_dma_map(&pdev->dev, frag,
						offset, size, DMA_TO_DEVICE);
			if (dma_mapping_error(&pdev->dev, buffer_info->dma))
				goto dma_error;
			buffer_info->next_to_watch = i;

			len -= size;
			offset += size;
			count++;
		}
	}

	segs = skb_shinfo(skb)->gso_segs ?: 1;
	/* multiply data chunks by size of headers */
	bytecount = ((segs - 1) * skb_headlen(skb)) + skb->len;

	tx_ring->buffer_info[i].skb = skb;
	tx_ring->buffer_info[i].segs = segs;
	tx_ring->buffer_info[i].bytecount = bytecount;
	tx_ring->buffer_info[first].next_to_watch = i;

	return count;

dma_error:
	dev_err(&pdev->dev, "TX DMA map failed\n");
	buffer_info->dma = 0;
	if (count)
		count--;

	while (count--) {
		if (i == 0)
			i += tx_ring->count;
		i--;
		buffer_info = &tx_ring->buffer_info[i];
		e1000_unmap_and_free_tx_resource(adapter, buffer_info);
	}

	return 0;
}