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
typedef  int /*<<< orphan*/  u32 ;
struct xlgmac_pdata {unsigned int channel_count; scalar_t__ mac_regs; struct xlgmac_channel* channel_head; } ;
struct xlgmac_channel {int /*<<< orphan*/  rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_CR ; 
 int /*<<< orphan*/  DMA_CH_CR_SPH_LEN ; 
 int /*<<< orphan*/  DMA_CH_CR_SPH_POS ; 
 scalar_t__ MAC_RCR ; 
 int /*<<< orphan*/  MAC_RCR_HDSMS_LEN ; 
 int /*<<< orphan*/  MAC_RCR_HDSMS_POS ; 
 scalar_t__ XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XLGMAC_SPH_HDSMS_SIZE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xlgmac_config_sph_mode(struct xlgmac_pdata *pdata)
{
	struct xlgmac_channel *channel;
	unsigned int i;
	u32 regval;

	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		if (!channel->rx_ring)
			break;

		regval = readl(XLGMAC_DMA_REG(channel, DMA_CH_CR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_CR_SPH_POS,
					     DMA_CH_CR_SPH_LEN, 1);
		writel(regval, XLGMAC_DMA_REG(channel, DMA_CH_CR));
	}

	regval = readl(pdata->mac_regs + MAC_RCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_HDSMS_POS,
				     MAC_RCR_HDSMS_LEN,
				XLGMAC_SPH_HDSMS_SIZE);
	writel(regval, pdata->mac_regs + MAC_RCR);
}