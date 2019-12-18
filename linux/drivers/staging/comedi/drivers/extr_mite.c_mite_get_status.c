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
struct mite_channel {int done; int /*<<< orphan*/  channel; struct mite* mite; } ;
struct mite {int /*<<< orphan*/  lock; scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHOR_CLRDONE ; 
 unsigned int CHSR_DONE ; 
 scalar_t__ MITE_CHOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MITE_CHSR (int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned int mite_get_status(struct mite_channel *mite_chan)
{
	struct mite *mite = mite_chan->mite;
	unsigned int status;
	unsigned long flags;

	spin_lock_irqsave(&mite->lock, flags);
	status = readl(mite->mmio + MITE_CHSR(mite_chan->channel));
	if (status & CHSR_DONE) {
		mite_chan->done = 1;
		writel(CHOR_CLRDONE,
		       mite->mmio + MITE_CHOR(mite_chan->channel));
	}
	spin_unlock_irqrestore(&mite->lock, flags);
	return status;
}