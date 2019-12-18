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
struct xlgmac_pdata {unsigned int channel_count; int /*<<< orphan*/  pblx8; struct xlgmac_channel* channel_head; } ;
struct xlgmac_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_CR ; 
 int /*<<< orphan*/  DMA_CH_CR_PBLX8_LEN ; 
 int /*<<< orphan*/  DMA_CH_CR_PBLX8_POS ; 
 int /*<<< orphan*/  XLGMAC_DMA_REG (struct xlgmac_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlgmac_config_pblx8(struct xlgmac_pdata *pdata)
{
	struct xlgmac_channel *channel;
	unsigned int i;
	u32 regval;

	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		regval = readl(XLGMAC_DMA_REG(channel, DMA_CH_CR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_CR_PBLX8_POS,
					     DMA_CH_CR_PBLX8_LEN,
					pdata->pblx8);
		writel(regval, XLGMAC_DMA_REG(channel, DMA_CH_CR));
	}

	return 0;
}