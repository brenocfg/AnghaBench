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
struct mite_channel {int /*<<< orphan*/ * ring; int /*<<< orphan*/  channel; struct mite* mite; } ;
struct mite {int /*<<< orphan*/  lock; scalar_t__ mmio; } ;

/* Variables and functions */
 int CHCR_CLR_CONT_RB_IE ; 
 int CHCR_CLR_DMA_IE ; 
 int CHCR_CLR_DONE_IE ; 
 int CHCR_CLR_DRDY_IE ; 
 int CHCR_CLR_LC_IE ; 
 int CHCR_CLR_LINKP_IE ; 
 int CHCR_CLR_MRDY_IE ; 
 int CHCR_CLR_SAR_IE ; 
 scalar_t__ MITE_CHCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_dma_disarm (struct mite_channel*) ; 
 int /*<<< orphan*/  mite_dma_reset (struct mite_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void mite_release_channel(struct mite_channel *mite_chan)
{
	struct mite *mite = mite_chan->mite;
	unsigned long flags;

	/* spin lock to prevent races with mite_request_channel */
	spin_lock_irqsave(&mite->lock, flags);
	if (mite_chan->ring) {
		mite_dma_disarm(mite_chan);
		mite_dma_reset(mite_chan);
		/*
		 * disable all channel's interrupts (do it after disarm/reset so
		 * MITE_CHCR reg isn't changed while dma is still active!)
		 */
		writel(CHCR_CLR_DMA_IE | CHCR_CLR_LINKP_IE |
		       CHCR_CLR_SAR_IE | CHCR_CLR_DONE_IE |
		       CHCR_CLR_MRDY_IE | CHCR_CLR_DRDY_IE |
		       CHCR_CLR_LC_IE | CHCR_CLR_CONT_RB_IE,
		       mite->mmio + MITE_CHCR(mite_chan->channel));
		mite_chan->ring = NULL;
	}
	spin_unlock_irqrestore(&mite->lock, flags);
}