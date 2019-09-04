#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct dw_dma_chan {int /*<<< orphan*/  flags; TYPE_1__ chan; } ;
struct dw_dma {TYPE_2__* pdata; } ;
struct TYPE_4__ {scalar_t__ is_idma32; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_LO ; 
 int DWC_CFGL_CH_SUSP ; 
 int DWC_CFGL_FIFO_EMPTY ; 
 int /*<<< orphan*/  DW_DMA_IS_PAUSED ; 
 int IDMA32C_CFGL_CH_DRAIN ; 
 int channel_readl (struct dw_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_writel (struct dw_dma_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dwc_chan_pause(struct dw_dma_chan *dwc, bool drain)
{
	struct dw_dma *dw = to_dw_dma(dwc->chan.device);
	unsigned int		count = 20;	/* timeout iterations */
	u32			cfglo;

	cfglo = channel_readl(dwc, CFG_LO);
	if (dw->pdata->is_idma32) {
		if (drain)
			cfglo |= IDMA32C_CFGL_CH_DRAIN;
		else
			cfglo &= ~IDMA32C_CFGL_CH_DRAIN;
	}
	channel_writel(dwc, CFG_LO, cfglo | DWC_CFGL_CH_SUSP);
	while (!(channel_readl(dwc, CFG_LO) & DWC_CFGL_FIFO_EMPTY) && count--)
		udelay(2);

	set_bit(DW_DMA_IS_PAUSED, &dwc->flags);
}