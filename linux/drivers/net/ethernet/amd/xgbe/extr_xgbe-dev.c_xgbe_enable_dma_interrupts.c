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
struct TYPE_2__ {int /*<<< orphan*/  version; } ;
struct xgbe_prv_data {unsigned int channel_count; scalar_t__ channel_irq_mode; int /*<<< orphan*/  per_channel_irq; struct xgbe_channel** channel; TYPE_1__ hw_feat; } ;
struct xgbe_channel {scalar_t__ curr_ier; scalar_t__ rx_ring; scalar_t__ tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIE ; 
 int /*<<< orphan*/  AIE20 ; 
 int /*<<< orphan*/  DMA_CH_IER ; 
 int /*<<< orphan*/  DMA_CH_SR ; 
 int /*<<< orphan*/  DMA_MR ; 
 int /*<<< orphan*/  FBEE ; 
 int /*<<< orphan*/  INTM ; 
 int /*<<< orphan*/  MAC_VR ; 
 int /*<<< orphan*/  NIE ; 
 int /*<<< orphan*/  NIE20 ; 
 int /*<<< orphan*/  RBUE ; 
 int /*<<< orphan*/  RIE ; 
 int /*<<< orphan*/  SNPSVER ; 
 int /*<<< orphan*/  TIE ; 
 scalar_t__ XGMAC_DMA_IOREAD (struct xgbe_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE (struct xgbe_channel*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int XGMAC_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_enable_dma_interrupts(struct xgbe_prv_data *pdata)
{
	struct xgbe_channel *channel;
	unsigned int i, ver;

	/* Set the interrupt mode if supported */
	if (pdata->channel_irq_mode)
		XGMAC_IOWRITE_BITS(pdata, DMA_MR, INTM,
				   pdata->channel_irq_mode);

	ver = XGMAC_GET_BITS(pdata->hw_feat.version, MAC_VR, SNPSVER);

	for (i = 0; i < pdata->channel_count; i++) {
		channel = pdata->channel[i];

		/* Clear all the interrupts which are set */
		XGMAC_DMA_IOWRITE(channel, DMA_CH_SR,
				  XGMAC_DMA_IOREAD(channel, DMA_CH_SR));

		/* Clear all interrupt enable bits */
		channel->curr_ier = 0;

		/* Enable following interrupts
		 *   NIE  - Normal Interrupt Summary Enable
		 *   AIE  - Abnormal Interrupt Summary Enable
		 *   FBEE - Fatal Bus Error Enable
		 */
		if (ver < 0x21) {
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, NIE20, 1);
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, AIE20, 1);
		} else {
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, NIE, 1);
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, AIE, 1);
		}
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, FBEE, 1);

		if (channel->tx_ring) {
			/* Enable the following Tx interrupts
			 *   TIE  - Transmit Interrupt Enable (unless using
			 *          per channel interrupts in edge triggered
			 *          mode)
			 */
			if (!pdata->per_channel_irq || pdata->channel_irq_mode)
				XGMAC_SET_BITS(channel->curr_ier,
					       DMA_CH_IER, TIE, 1);
		}
		if (channel->rx_ring) {
			/* Enable following Rx interrupts
			 *   RBUE - Receive Buffer Unavailable Enable
			 *   RIE  - Receive Interrupt Enable (unless using
			 *          per channel interrupts in edge triggered
			 *          mode)
			 */
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RBUE, 1);
			if (!pdata->per_channel_irq || pdata->channel_irq_mode)
				XGMAC_SET_BITS(channel->curr_ier,
					       DMA_CH_IER, RIE, 1);
		}

		XGMAC_DMA_IOWRITE(channel, DMA_CH_IER, channel->curr_ier);
	}
}