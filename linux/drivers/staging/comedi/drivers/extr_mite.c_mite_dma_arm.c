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
struct mite_channel {int /*<<< orphan*/  channel; scalar_t__ done; struct mite* mite; } ;
struct mite {int /*<<< orphan*/  lock; scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHOR_START ; 
 scalar_t__ MITE_CHOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void mite_dma_arm(struct mite_channel *mite_chan)
{
	struct mite *mite = mite_chan->mite;
	unsigned long flags;

	/*
	 * memory barrier is intended to insure any twiddling with the buffer
	 * is done before writing to the mite to arm dma transfer
	 */
	smp_mb();
	spin_lock_irqsave(&mite->lock, flags);
	mite_chan->done = 0;
	/* arm */
	writel(CHOR_START, mite->mmio + MITE_CHOR(mite_chan->channel));
	spin_unlock_irqrestore(&mite->lock, flags);
}