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
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct dw_dma_chan {TYPE_1__* tx_node_active; int /*<<< orphan*/  mask; TYPE_2__ chan; } ;
struct dw_dma {int dummy; } ;
struct dw_desc {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_EN ; 
 int /*<<< orphan*/  CTL_HI ; 
 int /*<<< orphan*/  CTL_LO ; 
 int /*<<< orphan*/  DAR ; 
 int DWC_CTLL_INT_EN ; 
 int /*<<< orphan*/  SAR ; 
 int /*<<< orphan*/  channel_set_bit (struct dw_dma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_writel (struct dw_dma_chan*,int /*<<< orphan*/ ,int) ; 
 int ctlhi ; 
 int dar ; 
 int lli_read (struct dw_desc*,int) ; 
 int sar ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dwc_do_single_block(struct dw_dma_chan *dwc,
				       struct dw_desc *desc)
{
	struct dw_dma	*dw = to_dw_dma(dwc->chan.device);
	u32		ctllo;

	/*
	 * Software emulation of LLP mode relies on interrupts to continue
	 * multi block transfer.
	 */
	ctllo = lli_read(desc, ctllo) | DWC_CTLL_INT_EN;

	channel_writel(dwc, SAR, lli_read(desc, sar));
	channel_writel(dwc, DAR, lli_read(desc, dar));
	channel_writel(dwc, CTL_LO, ctllo);
	channel_writel(dwc, CTL_HI, lli_read(desc, ctlhi));
	channel_set_bit(dw, CH_EN, dwc->mask);

	/* Move pointer to next descriptor */
	dwc->tx_node_active = dwc->tx_node_active->next;
}