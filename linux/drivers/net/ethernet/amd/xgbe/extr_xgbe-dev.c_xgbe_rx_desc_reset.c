#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xgbe_ring_desc {void* desc3; void* desc2; void* desc1; void* desc0; } ;
struct TYPE_5__ {scalar_t__ dma_off; scalar_t__ dma_base; } ;
struct TYPE_4__ {scalar_t__ dma_off; scalar_t__ dma_base; } ;
struct TYPE_6__ {TYPE_2__ buf; TYPE_1__ hdr; } ;
struct xgbe_ring_data {TYPE_3__ rx; struct xgbe_ring_desc* rdesc; } ;
struct xgbe_prv_data {unsigned int rx_usecs; unsigned int rx_frames; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTE ; 
 int /*<<< orphan*/  OWN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3 ; 
 int /*<<< orphan*/  XGMAC_SET_BITS_LE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void xgbe_rx_desc_reset(struct xgbe_prv_data *pdata,
			       struct xgbe_ring_data *rdata, unsigned int index)
{
	struct xgbe_ring_desc *rdesc = rdata->rdesc;
	unsigned int rx_usecs = pdata->rx_usecs;
	unsigned int rx_frames = pdata->rx_frames;
	unsigned int inte;
	dma_addr_t hdr_dma, buf_dma;

	if (!rx_usecs && !rx_frames) {
		/* No coalescing, interrupt for every descriptor */
		inte = 1;
	} else {
		/* Set interrupt based on Rx frame coalescing setting */
		if (rx_frames && !((index + 1) % rx_frames))
			inte = 1;
		else
			inte = 0;
	}

	/* Reset the Rx descriptor
	 *   Set buffer 1 (lo) address to header dma address (lo)
	 *   Set buffer 1 (hi) address to header dma address (hi)
	 *   Set buffer 2 (lo) address to buffer dma address (lo)
	 *   Set buffer 2 (hi) address to buffer dma address (hi) and
	 *     set control bits OWN and INTE
	 */
	hdr_dma = rdata->rx.hdr.dma_base + rdata->rx.hdr.dma_off;
	buf_dma = rdata->rx.buf.dma_base + rdata->rx.buf.dma_off;
	rdesc->desc0 = cpu_to_le32(lower_32_bits(hdr_dma));
	rdesc->desc1 = cpu_to_le32(upper_32_bits(hdr_dma));
	rdesc->desc2 = cpu_to_le32(lower_32_bits(buf_dma));
	rdesc->desc3 = cpu_to_le32(upper_32_bits(buf_dma));

	XGMAC_SET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, INTE, inte);

	/* Since the Rx DMA engine is likely running, make sure everything
	 * is written to the descriptor(s) before setting the OWN bit
	 * for the descriptor
	 */
	dma_wmb();

	XGMAC_SET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, OWN, 1);

	/* Make sure ownership is written to the descriptor */
	dma_wmb();
}