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
struct xgbe_ring_data {int /*<<< orphan*/  rdesc_dma; } ;
struct xgbe_ring {unsigned int cur; unsigned int rdesc_count; } ;
struct xgbe_prv_data {int dummy; } ;
struct xgbe_channel {struct xgbe_ring* rx_ring; struct xgbe_prv_data* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  DMA_CH_RDLR_HI ; 
 int /*<<< orphan*/  DMA_CH_RDLR_LO ; 
 int /*<<< orphan*/  DMA_CH_RDRLR ; 
 int /*<<< orphan*/  DMA_CH_RDTR_LO ; 
 struct xgbe_ring_data* XGBE_GET_DESC_DATA (struct xgbe_ring*,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE (struct xgbe_channel*,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_rx_desc_reset (struct xgbe_prv_data*,struct xgbe_ring_data*,unsigned int) ; 

__attribute__((used)) static void xgbe_rx_desc_init(struct xgbe_channel *channel)
{
	struct xgbe_prv_data *pdata = channel->pdata;
	struct xgbe_ring *ring = channel->rx_ring;
	struct xgbe_ring_data *rdata;
	unsigned int start_index = ring->cur;
	unsigned int i;

	DBGPR("-->rx_desc_init\n");

	/* Initialize all descriptors */
	for (i = 0; i < ring->rdesc_count; i++) {
		rdata = XGBE_GET_DESC_DATA(ring, i);

		/* Initialize Rx descriptor */
		xgbe_rx_desc_reset(pdata, rdata, i);
	}

	/* Update the total number of Rx descriptors */
	XGMAC_DMA_IOWRITE(channel, DMA_CH_RDRLR, ring->rdesc_count - 1);

	/* Update the starting address of descriptor ring */
	rdata = XGBE_GET_DESC_DATA(ring, start_index);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_RDLR_HI,
			  upper_32_bits(rdata->rdesc_dma));
	XGMAC_DMA_IOWRITE(channel, DMA_CH_RDLR_LO,
			  lower_32_bits(rdata->rdesc_dma));

	/* Update the Rx Descriptor Tail Pointer */
	rdata = XGBE_GET_DESC_DATA(ring, start_index + ring->rdesc_count - 1);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_RDTR_LO,
			  lower_32_bits(rdata->rdesc_dma));

	DBGPR("<--rx_desc_init\n");
}