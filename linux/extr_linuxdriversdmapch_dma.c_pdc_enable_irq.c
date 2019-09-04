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
struct pch_dma {int dummy; } ;
struct dma_chan {int chan_id; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL2 ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int dma_readl (struct pch_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_writel (struct pch_dma*,int /*<<< orphan*/ ,int) ; 
 struct pch_dma* to_pd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdc_enable_irq(struct dma_chan *chan, int enable)
{
	struct pch_dma *pd = to_pd(chan->device);
	u32 val;
	int pos;

	if (chan->chan_id < 8)
		pos = chan->chan_id;
	else
		pos = chan->chan_id + 8;

	val = dma_readl(pd, CTL2);

	if (enable)
		val |= 0x1 << pos;
	else
		val &= ~(0x1 << pos);

	dma_writel(pd, CTL2, val);

	dev_dbg(chan2dev(chan), "pdc_enable_irq: chan %d -> %x\n",
		chan->chan_id, val);
}