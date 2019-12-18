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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/ * data_len; struct ena_rx_buffer* len; int /*<<< orphan*/  protocol; } ;
struct ena_rx_buffer {int page_offset; int /*<<< orphan*/ * page; int /*<<< orphan*/  ena_buf; } ;
struct ena_ring {size_t rx_copybreak; size_t* free_ids; struct ena_rx_buffer* rx_buffer_info; int /*<<< orphan*/  ring_size; int /*<<< orphan*/  netdev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;
struct ena_com_rx_buf_info {size_t len; size_t req_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ENA_PAGE_SIZE ; 
 size_t ENA_RX_RING_IDX_ADD (size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t ENA_RX_RING_IDX_NEXT (size_t,int /*<<< orphan*/ ) ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ena_alloc_skb (struct ena_ring*,int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netif_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ena_rx_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  paddr ; 
 void* page_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (void*) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void*,size_t) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *ena_rx_skb(struct ena_ring *rx_ring,
				  struct ena_com_rx_buf_info *ena_bufs,
				  u32 descs,
				  u16 *next_to_clean)
{
	struct sk_buff *skb;
	struct ena_rx_buffer *rx_info;
	u16 len, req_id, buf = 0;
	void *va;

	len = ena_bufs[buf].len;
	req_id = ena_bufs[buf].req_id;
	rx_info = &rx_ring->rx_buffer_info[req_id];

	if (unlikely(!rx_info->page)) {
		netif_err(rx_ring->adapter, rx_err, rx_ring->netdev,
			  "Page is NULL\n");
		return NULL;
	}

	netif_dbg(rx_ring->adapter, rx_status, rx_ring->netdev,
		  "rx_info %p page %p\n",
		  rx_info, rx_info->page);

	/* save virt address of first buffer */
	va = page_address(rx_info->page) + rx_info->page_offset;
	prefetch(va + NET_IP_ALIGN);

	if (len <= rx_ring->rx_copybreak) {
		skb = ena_alloc_skb(rx_ring, false);
		if (unlikely(!skb))
			return NULL;

		netif_dbg(rx_ring->adapter, rx_status, rx_ring->netdev,
			  "rx allocated small packet. len %d. data_len %d\n",
			  skb->len, skb->data_len);

		/* sync this buffer for CPU use */
		dma_sync_single_for_cpu(rx_ring->dev,
					dma_unmap_addr(&rx_info->ena_buf, paddr),
					len,
					DMA_FROM_DEVICE);
		skb_copy_to_linear_data(skb, va, len);
		dma_sync_single_for_device(rx_ring->dev,
					   dma_unmap_addr(&rx_info->ena_buf, paddr),
					   len,
					   DMA_FROM_DEVICE);

		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, rx_ring->netdev);
		rx_ring->free_ids[*next_to_clean] = req_id;
		*next_to_clean = ENA_RX_RING_IDX_ADD(*next_to_clean, descs,
						     rx_ring->ring_size);
		return skb;
	}

	skb = ena_alloc_skb(rx_ring, true);
	if (unlikely(!skb))
		return NULL;

	do {
		dma_unmap_page(rx_ring->dev,
			       dma_unmap_addr(&rx_info->ena_buf, paddr),
			       ENA_PAGE_SIZE, DMA_FROM_DEVICE);

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_info->page,
				rx_info->page_offset, len, ENA_PAGE_SIZE);

		netif_dbg(rx_ring->adapter, rx_status, rx_ring->netdev,
			  "rx skb updated. len %d. data_len %d\n",
			  skb->len, skb->data_len);

		rx_info->page = NULL;

		rx_ring->free_ids[*next_to_clean] = req_id;
		*next_to_clean =
			ENA_RX_RING_IDX_NEXT(*next_to_clean,
					     rx_ring->ring_size);
		if (likely(--descs == 0))
			break;

		buf++;
		len = ena_bufs[buf].len;
		req_id = ena_bufs[buf].req_id;
		rx_info = &rx_ring->rx_buffer_info[req_id];
	} while (1);

	return skb;
}