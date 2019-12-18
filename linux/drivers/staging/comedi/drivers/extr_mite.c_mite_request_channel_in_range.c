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
struct mite_ring {int dummy; } ;
struct mite_channel {struct mite_ring* ring; } ;
struct mite {int /*<<< orphan*/  lock; struct mite_channel* channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct mite_channel *mite_request_channel_in_range(struct mite *mite,
						   struct mite_ring *ring,
						   unsigned int min_channel,
						   unsigned int max_channel)
{
	struct mite_channel *mite_chan = NULL;
	unsigned long flags;
	int i;

	/*
	 * spin lock so mite_release_channel can be called safely
	 * from interrupts
	 */
	spin_lock_irqsave(&mite->lock, flags);
	for (i = min_channel; i <= max_channel; ++i) {
		mite_chan = &mite->channels[i];
		if (!mite_chan->ring) {
			mite_chan->ring = ring;
			break;
		}
		mite_chan = NULL;
	}
	spin_unlock_irqrestore(&mite->lock, flags);
	return mite_chan;
}