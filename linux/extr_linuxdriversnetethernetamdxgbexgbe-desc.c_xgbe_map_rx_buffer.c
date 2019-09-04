#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  hdr; } ;
struct xgbe_ring_data {TYPE_1__ rx; } ;
struct TYPE_5__ {int /*<<< orphan*/  pages; } ;
struct xgbe_ring {TYPE_2__ rx_buf_pa; TYPE_2__ rx_hdr_pa; int /*<<< orphan*/  node; } ;
struct xgbe_prv_data {int /*<<< orphan*/  rx_buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALLOC_COSTLY_ORDER ; 
 int /*<<< orphan*/  XGBE_SKB_ALLOC_SIZE ; 
 int xgbe_alloc_pages (struct xgbe_prv_data*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_set_buffer_data (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_map_rx_buffer(struct xgbe_prv_data *pdata,
			      struct xgbe_ring *ring,
			      struct xgbe_ring_data *rdata)
{
	int ret;

	if (!ring->rx_hdr_pa.pages) {
		ret = xgbe_alloc_pages(pdata, &ring->rx_hdr_pa, 0, ring->node);
		if (ret)
			return ret;
	}

	if (!ring->rx_buf_pa.pages) {
		ret = xgbe_alloc_pages(pdata, &ring->rx_buf_pa,
				       PAGE_ALLOC_COSTLY_ORDER, ring->node);
		if (ret)
			return ret;
	}

	/* Set up the header page info */
	xgbe_set_buffer_data(&rdata->rx.hdr, &ring->rx_hdr_pa,
			     XGBE_SKB_ALLOC_SIZE);

	/* Set up the buffer page info */
	xgbe_set_buffer_data(&rdata->rx.buf, &ring->rx_buf_pa,
			     pdata->rx_buf_size);

	return 0;
}