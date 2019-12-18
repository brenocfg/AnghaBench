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
struct tsi721_bdma_chan {int /*<<< orphan*/  lock; scalar_t__ regs; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 scalar_t__ TSI721_DMAC_CTL ; 
 int /*<<< orphan*/  TSI721_DMAC_CTL_SUSP ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi721_dma_is_idle (struct tsi721_bdma_chan*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tsi721_dma_stop(struct tsi721_bdma_chan *bdma_chan)
{
	if (!bdma_chan->active)
		return;
	spin_lock_bh(&bdma_chan->lock);
	if (!tsi721_dma_is_idle(bdma_chan)) {
		int timeout = 100000;

		/* stop the transfer in progress */
		iowrite32(TSI721_DMAC_CTL_SUSP,
			  bdma_chan->regs + TSI721_DMAC_CTL);

		/* Wait until DMA channel stops */
		while (!tsi721_dma_is_idle(bdma_chan) && --timeout)
			udelay(1);
	}

	spin_unlock_bh(&bdma_chan->lock);
}