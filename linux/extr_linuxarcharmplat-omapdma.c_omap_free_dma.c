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
struct TYPE_4__ {int dev_id; int next_lch; int /*<<< orphan*/ * callback; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dma_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 TYPE_2__* dma_chan ; 
 int /*<<< orphan*/  dma_chan_lock ; 
 scalar_t__ dma_omap2plus () ; 
 int /*<<< orphan*/  omap2_disable_irq_lch (int) ; 
 int /*<<< orphan*/  omap_clear_dma (int) ; 
 int /*<<< orphan*/  omap_disable_channel_irq (int) ; 
 TYPE_1__* p ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void omap_free_dma(int lch)
{
	unsigned long flags;

	if (dma_chan[lch].dev_id == -1) {
		pr_err("omap_dma: trying to free unallocated DMA channel %d\n",
		       lch);
		return;
	}

	/* Disable interrupt for logical channel */
	if (dma_omap2plus())
		omap2_disable_irq_lch(lch);

	/* Disable all DMA interrupts for the channel. */
	omap_disable_channel_irq(lch);

	/* Make sure the DMA transfer is stopped. */
	p->dma_write(0, CCR, lch);

	/* Clear registers */
	if (dma_omap2plus())
		omap_clear_dma(lch);

	spin_lock_irqsave(&dma_chan_lock, flags);
	dma_chan[lch].dev_id = -1;
	dma_chan[lch].next_lch = -1;
	dma_chan[lch].callback = NULL;
	spin_unlock_irqrestore(&dma_chan_lock, flags);
}