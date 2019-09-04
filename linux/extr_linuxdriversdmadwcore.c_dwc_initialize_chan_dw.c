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
typedef  int u32 ;
struct TYPE_2__ {int hs_polarity; int /*<<< orphan*/  src_id; int /*<<< orphan*/  dst_id; } ;
struct dw_dma_chan {TYPE_1__ dws; int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_HI ; 
 int /*<<< orphan*/  CFG_LO ; 
 int DWC_CFGH_DST_PER (int /*<<< orphan*/ ) ; 
 int DWC_CFGH_FIFO_MODE ; 
 int DWC_CFGH_SRC_PER (int /*<<< orphan*/ ) ; 
 int DWC_CFGL_CH_PRIOR (int /*<<< orphan*/ ) ; 
 int DWC_CFGL_HS_DST_POL ; 
 int DWC_CFGL_HS_SRC_POL ; 
 int /*<<< orphan*/  channel_writel (struct dw_dma_chan*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc_initialize_chan_dw(struct dw_dma_chan *dwc)
{
	u32 cfghi = DWC_CFGH_FIFO_MODE;
	u32 cfglo = DWC_CFGL_CH_PRIOR(dwc->priority);
	bool hs_polarity = dwc->dws.hs_polarity;

	cfghi |= DWC_CFGH_DST_PER(dwc->dws.dst_id);
	cfghi |= DWC_CFGH_SRC_PER(dwc->dws.src_id);

	/* Set polarity of handshake interface */
	cfglo |= hs_polarity ? DWC_CFGL_HS_DST_POL | DWC_CFGL_HS_SRC_POL : 0;

	channel_writel(dwc, CFG_LO, cfglo);
	channel_writel(dwc, CFG_HI, cfghi);
}