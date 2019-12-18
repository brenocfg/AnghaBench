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
struct TYPE_4__ {scalar_t__ pages_dma; scalar_t__ pages_offset; scalar_t__ pages_len; int /*<<< orphan*/ * pages; } ;
struct TYPE_3__ {scalar_t__ pages_dma; scalar_t__ pages_offset; scalar_t__ pages_len; int /*<<< orphan*/ * pages; } ;
struct xlgmac_ring {unsigned int dma_desc_count; int /*<<< orphan*/ * dma_desc_head; int /*<<< orphan*/  dma_desc_head_addr; TYPE_2__ rx_buf_pa; TYPE_1__ rx_hdr_pa; int /*<<< orphan*/ * desc_data_head; } ;
struct xlgmac_pdata {int /*<<< orphan*/  dev; } ;
struct xlgmac_dma_desc {int dummy; } ;
struct xlgmac_desc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,unsigned int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlgmac_unmap_desc_data (struct xlgmac_pdata*,struct xlgmac_desc_data*) ; 

__attribute__((used)) static void xlgmac_free_ring(struct xlgmac_pdata *pdata,
			     struct xlgmac_ring *ring)
{
	struct xlgmac_desc_data *desc_data;
	unsigned int i;

	if (!ring)
		return;

	if (ring->desc_data_head) {
		for (i = 0; i < ring->dma_desc_count; i++) {
			desc_data = XLGMAC_GET_DESC_DATA(ring, i);
			xlgmac_unmap_desc_data(pdata, desc_data);
		}

		kfree(ring->desc_data_head);
		ring->desc_data_head = NULL;
	}

	if (ring->rx_hdr_pa.pages) {
		dma_unmap_page(pdata->dev, ring->rx_hdr_pa.pages_dma,
			       ring->rx_hdr_pa.pages_len, DMA_FROM_DEVICE);
		put_page(ring->rx_hdr_pa.pages);

		ring->rx_hdr_pa.pages = NULL;
		ring->rx_hdr_pa.pages_len = 0;
		ring->rx_hdr_pa.pages_offset = 0;
		ring->rx_hdr_pa.pages_dma = 0;
	}

	if (ring->rx_buf_pa.pages) {
		dma_unmap_page(pdata->dev, ring->rx_buf_pa.pages_dma,
			       ring->rx_buf_pa.pages_len, DMA_FROM_DEVICE);
		put_page(ring->rx_buf_pa.pages);

		ring->rx_buf_pa.pages = NULL;
		ring->rx_buf_pa.pages_len = 0;
		ring->rx_buf_pa.pages_offset = 0;
		ring->rx_buf_pa.pages_dma = 0;
	}

	if (ring->dma_desc_head) {
		dma_free_coherent(pdata->dev,
				  (sizeof(struct xlgmac_dma_desc) *
				  ring->dma_desc_count),
				  ring->dma_desc_head,
				  ring->dma_desc_head_addr);
		ring->dma_desc_head = NULL;
	}
}