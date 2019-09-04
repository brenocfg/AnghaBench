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
struct dw_dma_chan {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HI ; 
 int /*<<< orphan*/  CTL_LO ; 
 int /*<<< orphan*/  DAR ; 
 int /*<<< orphan*/  LLP ; 
 int /*<<< orphan*/  SAR ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_readl (struct dw_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dwc_dump_chan_regs(struct dw_dma_chan *dwc)
{
	dev_err(chan2dev(&dwc->chan),
		"  SAR: 0x%x DAR: 0x%x LLP: 0x%x CTL: 0x%x:%08x\n",
		channel_readl(dwc, SAR),
		channel_readl(dwc, DAR),
		channel_readl(dwc, LLP),
		channel_readl(dwc, CTL_HI),
		channel_readl(dwc, CTL_LO));
}