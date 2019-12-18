#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xgbe_ring_desc {int dummy; } ;
struct xgbe_ring_data {int rdesc_dma; struct xgbe_ring_desc* rdesc; } ;
struct xgbe_ring {int rdesc_dma; unsigned int rdesc_count; scalar_t__ dirty; scalar_t__ cur; struct xgbe_ring_desc* rdesc; } ;
struct xgbe_hw_if {int /*<<< orphan*/  (* rx_desc_init ) (struct xgbe_channel*) ;} ;
struct xgbe_prv_data {unsigned int channel_count; struct xgbe_channel** channel; struct xgbe_hw_if hw_if; } ;
struct xgbe_channel {struct xgbe_ring* rx_ring; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 struct xgbe_ring_data* XGBE_GET_DESC_DATA (struct xgbe_ring*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_channel*) ; 
 scalar_t__ xgbe_map_rx_buffer (struct xgbe_prv_data*,struct xgbe_ring*,struct xgbe_ring_data*) ; 

__attribute__((used)) static void xgbe_wrapper_rx_descriptor_init(struct xgbe_prv_data *pdata)
{
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_channel *channel;
	struct xgbe_ring *ring;
	struct xgbe_ring_desc *rdesc;
	struct xgbe_ring_data *rdata;
	dma_addr_t rdesc_dma;
	unsigned int i, j;

	DBGPR("-->xgbe_wrapper_rx_descriptor_init\n");

	for (i = 0; i < pdata->channel_count; i++) {
		channel = pdata->channel[i];
		ring = channel->rx_ring;
		if (!ring)
			break;

		rdesc = ring->rdesc;
		rdesc_dma = ring->rdesc_dma;

		for (j = 0; j < ring->rdesc_count; j++) {
			rdata = XGBE_GET_DESC_DATA(ring, j);

			rdata->rdesc = rdesc;
			rdata->rdesc_dma = rdesc_dma;

			if (xgbe_map_rx_buffer(pdata, ring, rdata))
				break;

			rdesc++;
			rdesc_dma += sizeof(struct xgbe_ring_desc);
		}

		ring->cur = 0;
		ring->dirty = 0;

		hw_if->rx_desc_init(channel);
	}

	DBGPR("<--xgbe_wrapper_rx_descriptor_init\n");
}