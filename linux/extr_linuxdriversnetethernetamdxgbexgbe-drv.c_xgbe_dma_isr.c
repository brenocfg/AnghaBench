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
struct xgbe_prv_data {scalar_t__ channel_irq_mode; } ;
struct xgbe_channel {int /*<<< orphan*/  napi; int /*<<< orphan*/  dma_irq; struct xgbe_prv_data* pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_SR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RI ; 
 int /*<<< orphan*/  TI ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE (struct xgbe_channel*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_disable_rx_tx_int (struct xgbe_prv_data*,struct xgbe_channel*) ; 

__attribute__((used)) static irqreturn_t xgbe_dma_isr(int irq, void *data)
{
	struct xgbe_channel *channel = data;
	struct xgbe_prv_data *pdata = channel->pdata;
	unsigned int dma_status;

	/* Per channel DMA interrupts are enabled, so we use the per
	 * channel napi structure and not the private data napi structure
	 */
	if (napi_schedule_prep(&channel->napi)) {
		/* Disable Tx and Rx interrupts */
		if (pdata->channel_irq_mode)
			xgbe_disable_rx_tx_int(pdata, channel);
		else
			disable_irq_nosync(channel->dma_irq);

		/* Turn on polling */
		__napi_schedule_irqoff(&channel->napi);
	}

	/* Clear Tx/Rx signals */
	dma_status = 0;
	XGMAC_SET_BITS(dma_status, DMA_CH_SR, TI, 1);
	XGMAC_SET_BITS(dma_status, DMA_CH_SR, RI, 1);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_SR, dma_status);

	return IRQ_HANDLED;
}