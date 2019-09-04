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
struct dw_dma_chan {int mask; } ;
struct dw_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_EN ; 
 int /*<<< orphan*/  channel_clear_bit (struct dw_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dma_readl (struct dw_dma*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dwc_chan_disable(struct dw_dma *dw, struct dw_dma_chan *dwc)
{
	channel_clear_bit(dw, CH_EN, dwc->mask);
	while (dma_readl(dw, CH_EN) & dwc->mask)
		cpu_relax();
}