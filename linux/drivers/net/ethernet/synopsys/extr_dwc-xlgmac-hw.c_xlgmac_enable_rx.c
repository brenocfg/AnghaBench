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
struct xlgmac_pdata {unsigned int channel_count; unsigned int rx_q_count; scalar_t__ mac_regs; struct xlgmac_channel* channel_head; } ;
struct xlgmac_channel {int /*<<< orphan*/  rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_RCR ; 
 int /*<<< orphan*/  DMA_CH_RCR_SR_LEN ; 
 int /*<<< orphan*/  DMA_CH_RCR_SR_POS ; 
 scalar_t__ MAC_RCR ; 
 int /*<<< orphan*/  MAC_RCR_ACS_LEN ; 
 int /*<<< orphan*/  MAC_RCR_ACS_POS ; 
 int /*<<< orphan*/  MAC_RCR_CST_LEN ; 
 int /*<<< orphan*/  MAC_RCR_CST_POS ; 
 int /*<<< orphan*/  MAC_RCR_DCRCC_LEN ; 
 int /*<<< orphan*/  MAC_RCR_DCRCC_POS ; 
 int /*<<< orphan*/  MAC_RCR_RE_LEN ; 
 int /*<<< orphan*/  MAC_RCR_RE_POS ; 
 scalar_t__ MAC_RQC0R ; 
 scalar_t__ XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
 unsigned int XLGMAC_SET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void xlgmac_enable_rx(struct xlgmac_pdata *pdata)
{
	struct xlgmac_channel *channel;
	unsigned int regval, i;

	/* Enable each Rx DMA channel */
	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		if (!channel->rx_ring)
			break;

		regval = readl(XLGMAC_DMA_REG(channel, DMA_CH_RCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_RCR_SR_POS,
					     DMA_CH_RCR_SR_LEN, 1);
		writel(regval, XLGMAC_DMA_REG(channel, DMA_CH_RCR));
	}

	/* Enable each Rx queue */
	regval = 0;
	for (i = 0; i < pdata->rx_q_count; i++)
		regval |= (0x02 << (i << 1));
	writel(regval, pdata->mac_regs + MAC_RQC0R);

	/* Enable MAC Rx */
	regval = readl(pdata->mac_regs + MAC_RCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_DCRCC_POS,
				     MAC_RCR_DCRCC_LEN, 1);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_CST_POS,
				     MAC_RCR_CST_LEN, 1);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_ACS_POS,
				     MAC_RCR_ACS_LEN, 1);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_RE_POS,
				     MAC_RCR_RE_LEN, 1);
	writel(regval, pdata->mac_regs + MAC_RCR);
}