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
struct TYPE_2__ {int /*<<< orphan*/  fatal_bus_error; int /*<<< orphan*/  rx_buffer_unavailable; int /*<<< orphan*/  tx_buffer_unavailable; int /*<<< orphan*/  rx_process_stopped; int /*<<< orphan*/  tx_process_stopped; int /*<<< orphan*/  napi_poll_isr; } ;
struct xlgmac_hw_ops {int /*<<< orphan*/  (* rx_mmc_int ) (struct xlgmac_pdata*) ;int /*<<< orphan*/  (* tx_mmc_int ) (struct xlgmac_pdata*) ;} ;
struct xlgmac_pdata {unsigned int channel_count; scalar_t__ mac_regs; int /*<<< orphan*/  restart_work; TYPE_1__ stats; int /*<<< orphan*/  napi; int /*<<< orphan*/  per_channel_irq; int /*<<< orphan*/  netdev; struct xlgmac_channel* channel_head; struct xlgmac_hw_ops hw_ops; } ;
struct xlgmac_channel {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_SR ; 
 int /*<<< orphan*/  DMA_CH_SR_FBE_LEN ; 
 int /*<<< orphan*/  DMA_CH_SR_FBE_POS ; 
 int /*<<< orphan*/  DMA_CH_SR_RBU_LEN ; 
 int /*<<< orphan*/  DMA_CH_SR_RBU_POS ; 
 int /*<<< orphan*/  DMA_CH_SR_RI_LEN ; 
 int /*<<< orphan*/  DMA_CH_SR_RI_POS ; 
 int /*<<< orphan*/  DMA_CH_SR_RPS_LEN ; 
 int /*<<< orphan*/  DMA_CH_SR_RPS_POS ; 
 int /*<<< orphan*/  DMA_CH_SR_TBU_LEN ; 
 int /*<<< orphan*/  DMA_CH_SR_TBU_POS ; 
 int /*<<< orphan*/  DMA_CH_SR_TI_LEN ; 
 int /*<<< orphan*/  DMA_CH_SR_TI_POS ; 
 int /*<<< orphan*/  DMA_CH_SR_TPS_LEN ; 
 int /*<<< orphan*/  DMA_CH_SR_TPS_POS ; 
 scalar_t__ DMA_ISR ; 
 int /*<<< orphan*/  DMA_ISR_MACIS_LEN ; 
 int /*<<< orphan*/  DMA_ISR_MACIS_POS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MAC_ISR ; 
 int /*<<< orphan*/  MAC_ISR_MMCRXIS_LEN ; 
 int /*<<< orphan*/  MAC_ISR_MMCRXIS_POS ; 
 int /*<<< orphan*/  MAC_ISR_MMCTXIS_LEN ; 
 int /*<<< orphan*/  MAC_ISR_MMCTXIS_POS ; 
 scalar_t__ XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
 int XLGMAC_GET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intr ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (struct xlgmac_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  stub2 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  xlgmac_disable_rx_tx_ints (struct xlgmac_pdata*) ; 

__attribute__((used)) static irqreturn_t xlgmac_isr(int irq, void *data)
{
	unsigned int dma_isr, dma_ch_isr, mac_isr;
	struct xlgmac_pdata *pdata = data;
	struct xlgmac_channel *channel;
	struct xlgmac_hw_ops *hw_ops;
	unsigned int i, ti, ri;

	hw_ops = &pdata->hw_ops;

	/* The DMA interrupt status register also reports MAC and MTL
	 * interrupts. So for polling mode, we just need to check for
	 * this register to be non-zero
	 */
	dma_isr = readl(pdata->mac_regs + DMA_ISR);
	if (!dma_isr)
		return IRQ_HANDLED;

	netif_dbg(pdata, intr, pdata->netdev, "DMA_ISR=%#010x\n", dma_isr);

	for (i = 0; i < pdata->channel_count; i++) {
		if (!(dma_isr & (1 << i)))
			continue;

		channel = pdata->channel_head + i;

		dma_ch_isr = readl(XLGMAC_DMA_REG(channel, DMA_CH_SR));
		netif_dbg(pdata, intr, pdata->netdev, "DMA_CH%u_ISR=%#010x\n",
			  i, dma_ch_isr);

		/* The TI or RI interrupt bits may still be set even if using
		 * per channel DMA interrupts. Check to be sure those are not
		 * enabled before using the private data napi structure.
		 */
		ti = XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_TI_POS,
					 DMA_CH_SR_TI_LEN);
		ri = XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_RI_POS,
					 DMA_CH_SR_RI_LEN);
		if (!pdata->per_channel_irq && (ti || ri)) {
			if (napi_schedule_prep(&pdata->napi)) {
				/* Disable Tx and Rx interrupts */
				xlgmac_disable_rx_tx_ints(pdata);

				pdata->stats.napi_poll_isr++;
				/* Turn on polling */
				__napi_schedule_irqoff(&pdata->napi);
			}
		}

		if (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_TPS_POS,
					DMA_CH_SR_TPS_LEN))
			pdata->stats.tx_process_stopped++;

		if (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_RPS_POS,
					DMA_CH_SR_RPS_LEN))
			pdata->stats.rx_process_stopped++;

		if (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_TBU_POS,
					DMA_CH_SR_TBU_LEN))
			pdata->stats.tx_buffer_unavailable++;

		if (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_RBU_POS,
					DMA_CH_SR_RBU_LEN))
			pdata->stats.rx_buffer_unavailable++;

		/* Restart the device on a Fatal Bus Error */
		if (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_FBE_POS,
					DMA_CH_SR_FBE_LEN)) {
			pdata->stats.fatal_bus_error++;
			schedule_work(&pdata->restart_work);
		}

		/* Clear all interrupt signals */
		writel(dma_ch_isr, XLGMAC_DMA_REG(channel, DMA_CH_SR));
	}

	if (XLGMAC_GET_REG_BITS(dma_isr, DMA_ISR_MACIS_POS,
				DMA_ISR_MACIS_LEN)) {
		mac_isr = readl(pdata->mac_regs + MAC_ISR);

		if (XLGMAC_GET_REG_BITS(mac_isr, MAC_ISR_MMCTXIS_POS,
					MAC_ISR_MMCTXIS_LEN))
			hw_ops->tx_mmc_int(pdata);

		if (XLGMAC_GET_REG_BITS(mac_isr, MAC_ISR_MMCRXIS_POS,
					MAC_ISR_MMCRXIS_LEN))
			hw_ops->rx_mmc_int(pdata);
	}

	return IRQ_HANDLED;
}