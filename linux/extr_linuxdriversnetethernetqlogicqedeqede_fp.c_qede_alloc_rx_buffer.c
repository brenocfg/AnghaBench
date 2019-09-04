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
struct sw_rx_data {int /*<<< orphan*/  mapping; struct page* data; scalar_t__ page_offset; } ;
struct qede_rx_queue {int filled_buffers; size_t sw_rx_prod; scalar_t__ rx_headroom; int /*<<< orphan*/  rx_bd_ring; struct sw_rx_data* sw_rx_ring; int /*<<< orphan*/  dev; int /*<<< orphan*/  data_direction; } ;
struct page {int dummy; } ;
struct TYPE_2__ {void* lo; void* hi; } ;
struct eth_rx_bd {TYPE_1__ addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t NUM_RX_BDS_MAX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ lower_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ qed_chain_produce (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ upper_32_bits (int /*<<< orphan*/ ) ; 

int qede_alloc_rx_buffer(struct qede_rx_queue *rxq, bool allow_lazy)
{
	struct sw_rx_data *sw_rx_data;
	struct eth_rx_bd *rx_bd;
	dma_addr_t mapping;
	struct page *data;

	/* In case lazy-allocation is allowed, postpone allocation until the
	 * end of the NAPI run. We'd still need to make sure the Rx ring has
	 * sufficient buffers to guarantee an additional Rx interrupt.
	 */
	if (allow_lazy && likely(rxq->filled_buffers > 12)) {
		rxq->filled_buffers--;
		return 0;
	}

	data = alloc_pages(GFP_ATOMIC, 0);
	if (unlikely(!data))
		return -ENOMEM;

	/* Map the entire page as it would be used
	 * for multiple RX buffer segment size mapping.
	 */
	mapping = dma_map_page(rxq->dev, data, 0,
			       PAGE_SIZE, rxq->data_direction);
	if (unlikely(dma_mapping_error(rxq->dev, mapping))) {
		__free_page(data);
		return -ENOMEM;
	}

	sw_rx_data = &rxq->sw_rx_ring[rxq->sw_rx_prod & NUM_RX_BDS_MAX];
	sw_rx_data->page_offset = 0;
	sw_rx_data->data = data;
	sw_rx_data->mapping = mapping;

	/* Advance PROD and get BD pointer */
	rx_bd = (struct eth_rx_bd *)qed_chain_produce(&rxq->rx_bd_ring);
	WARN_ON(!rx_bd);
	rx_bd->addr.hi = cpu_to_le32(upper_32_bits(mapping));
	rx_bd->addr.lo = cpu_to_le32(lower_32_bits(mapping) +
				     rxq->rx_headroom);

	rxq->sw_rx_prod++;
	rxq->filled_buffers++;

	return 0;
}