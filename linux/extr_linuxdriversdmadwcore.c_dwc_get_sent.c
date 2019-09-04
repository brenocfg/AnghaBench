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
typedef  int u32 ;
struct dw_dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HI ; 
 int /*<<< orphan*/  CTL_LO ; 
 int block2bytes (struct dw_dma_chan*,int,int) ; 
 int channel_readl (struct dw_dma_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 dwc_get_sent(struct dw_dma_chan *dwc)
{
	u32 ctlhi = channel_readl(dwc, CTL_HI);
	u32 ctllo = channel_readl(dwc, CTL_LO);

	return block2bytes(dwc, ctlhi, ctllo >> 4 & 7);
}