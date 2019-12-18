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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct igbvf_ring {unsigned int next_to_use; unsigned int count; struct igbvf_buffer* buffer_info; } ;
struct igbvf_buffer {unsigned int length; int mapped_as_page; void* time_stamp; scalar_t__ dma; struct sk_buff* skb; } ;
struct igbvf_adapter {struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned int IGBVF_MAX_DATA_PER_TXD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  igbvf_put_txbuf (struct igbvf_adapter*,struct igbvf_buffer*) ; 
 void* jiffies ; 
 scalar_t__ skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/  const*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline int igbvf_tx_map_adv(struct igbvf_adapter *adapter,
				   struct igbvf_ring *tx_ring,
				   struct sk_buff *skb)
{
	struct igbvf_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	unsigned int len = skb_headlen(skb);
	unsigned int count = 0, i;
	unsigned int f;

	i = tx_ring->next_to_use;

	buffer_info = &tx_ring->buffer_info[i];
	BUG_ON(len >= IGBVF_MAX_DATA_PER_TXD);
	buffer_info->length = len;
	/* set time_stamp *before* dma to help avoid a possible race */
	buffer_info->time_stamp = jiffies;
	buffer_info->mapped_as_page = false;
	buffer_info->dma = dma_map_single(&pdev->dev, skb->data, len,
					  DMA_TO_DEVICE);
	if (dma_mapping_error(&pdev->dev, buffer_info->dma))
		goto dma_error;

	for (f = 0; f < skb_shinfo(skb)->nr_frags; f++) {
		const skb_frag_t *frag;

		count++;
		i++;
		if (i == tx_ring->count)
			i = 0;

		frag = &skb_shinfo(skb)->frags[f];
		len = skb_frag_size(frag);

		buffer_info = &tx_ring->buffer_info[i];
		BUG_ON(len >= IGBVF_MAX_DATA_PER_TXD);
		buffer_info->length = len;
		buffer_info->time_stamp = jiffies;
		buffer_info->mapped_as_page = true;
		buffer_info->dma = skb_frag_dma_map(&pdev->dev, frag, 0, len,
						    DMA_TO_DEVICE);
		if (dma_mapping_error(&pdev->dev, buffer_info->dma))
			goto dma_error;
	}

	tx_ring->buffer_info[i].skb = skb;

	return ++count;

dma_error:
	dev_err(&pdev->dev, "TX DMA map failed\n");

	/* clear timestamp and dma mappings for failed buffer_info mapping */
	buffer_info->dma = 0;
	buffer_info->time_stamp = 0;
	buffer_info->length = 0;
	buffer_info->mapped_as_page = false;
	if (count)
		count--;

	/* clear timestamp and dma mappings for remaining portion of packet */
	while (count--) {
		if (i == 0)
			i += tx_ring->count;
		i--;
		buffer_info = &tx_ring->buffer_info[i];
		igbvf_put_txbuf(adapter, buffer_info);
	}

	return 0;
}