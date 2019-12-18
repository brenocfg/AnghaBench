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
typedef  size_t u8 ;
typedef  size_t u16 ;
struct tx_packet_desc {int word3; } ;
struct sk_buff {size_t len; size_t data; scalar_t__ data_len; } ;
struct page {int dummy; } ;
struct atl1_tpd_ring {size_t count; struct atl1_buffer* buffer_info; int /*<<< orphan*/  next_to_use; } ;
struct atl1_buffer {size_t length; struct sk_buff* skb; void* dma; } ;
struct atl1_adapter {TYPE_2__* pdev; struct atl1_tpd_ring tpd_ring; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 size_t ATL1_MAX_TX_BUF_LEN ; 
 int /*<<< orphan*/  BUG_ON (struct sk_buff*) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TPD_SEGMENT_EN_MASK ; 
 int TPD_SEGMENT_EN_SHIFT ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long offset_in_page (size_t) ; 
 void* pci_map_page (TYPE_2__*,struct page*,unsigned long,size_t,int /*<<< orphan*/ ) ; 
 void* skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t skb_frag_size (int /*<<< orphan*/  const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 size_t skb_transport_offset (struct sk_buff*) ; 
 size_t tcp_hdrlen (struct sk_buff*) ; 
 struct page* virt_to_page (size_t) ; 

__attribute__((used)) static void atl1_tx_map(struct atl1_adapter *adapter, struct sk_buff *skb,
	struct tx_packet_desc *ptpd)
{
	struct atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	struct atl1_buffer *buffer_info;
	u16 buf_len = skb->len;
	struct page *page;
	unsigned long offset;
	unsigned int nr_frags;
	unsigned int f;
	int retval;
	u16 next_to_use;
	u16 data_len;
	u8 hdr_len;

	buf_len -= skb->data_len;
	nr_frags = skb_shinfo(skb)->nr_frags;
	next_to_use = atomic_read(&tpd_ring->next_to_use);
	buffer_info = &tpd_ring->buffer_info[next_to_use];
	BUG_ON(buffer_info->skb);
	/* put skb in last TPD */
	buffer_info->skb = NULL;

	retval = (ptpd->word3 >> TPD_SEGMENT_EN_SHIFT) & TPD_SEGMENT_EN_MASK;
	if (retval) {
		/* TSO */
		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		buffer_info->length = hdr_len;
		page = virt_to_page(skb->data);
		offset = offset_in_page(skb->data);
		buffer_info->dma = pci_map_page(adapter->pdev, page,
						offset, hdr_len,
						PCI_DMA_TODEVICE);

		if (++next_to_use == tpd_ring->count)
			next_to_use = 0;

		if (buf_len > hdr_len) {
			int i, nseg;

			data_len = buf_len - hdr_len;
			nseg = (data_len + ATL1_MAX_TX_BUF_LEN - 1) /
				ATL1_MAX_TX_BUF_LEN;
			for (i = 0; i < nseg; i++) {
				buffer_info =
				    &tpd_ring->buffer_info[next_to_use];
				buffer_info->skb = NULL;
				buffer_info->length =
				    (ATL1_MAX_TX_BUF_LEN >=
				     data_len) ? ATL1_MAX_TX_BUF_LEN : data_len;
				data_len -= buffer_info->length;
				page = virt_to_page(skb->data +
					(hdr_len + i * ATL1_MAX_TX_BUF_LEN));
				offset = offset_in_page(skb->data +
					(hdr_len + i * ATL1_MAX_TX_BUF_LEN));
				buffer_info->dma = pci_map_page(adapter->pdev,
					page, offset, buffer_info->length,
					PCI_DMA_TODEVICE);
				if (++next_to_use == tpd_ring->count)
					next_to_use = 0;
			}
		}
	} else {
		/* not TSO */
		buffer_info->length = buf_len;
		page = virt_to_page(skb->data);
		offset = offset_in_page(skb->data);
		buffer_info->dma = pci_map_page(adapter->pdev, page,
			offset, buf_len, PCI_DMA_TODEVICE);
		if (++next_to_use == tpd_ring->count)
			next_to_use = 0;
	}

	for (f = 0; f < nr_frags; f++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[f];
		u16 i, nseg;

		buf_len = skb_frag_size(frag);

		nseg = (buf_len + ATL1_MAX_TX_BUF_LEN - 1) /
			ATL1_MAX_TX_BUF_LEN;
		for (i = 0; i < nseg; i++) {
			buffer_info = &tpd_ring->buffer_info[next_to_use];
			BUG_ON(buffer_info->skb);

			buffer_info->skb = NULL;
			buffer_info->length = (buf_len > ATL1_MAX_TX_BUF_LEN) ?
				ATL1_MAX_TX_BUF_LEN : buf_len;
			buf_len -= buffer_info->length;
			buffer_info->dma = skb_frag_dma_map(&adapter->pdev->dev,
				frag, i * ATL1_MAX_TX_BUF_LEN,
				buffer_info->length, DMA_TO_DEVICE);

			if (++next_to_use == tpd_ring->count)
				next_to_use = 0;
		}
	}

	/* last tpd's buffer-info */
	buffer_info->skb = skb;
}