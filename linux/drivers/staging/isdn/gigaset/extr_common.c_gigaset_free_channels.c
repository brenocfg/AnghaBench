#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cardstate {int channels; int /*<<< orphan*/  lock; TYPE_1__* bcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CHANNEL ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void gigaset_free_channels(struct cardstate *cs)
{
	unsigned long flags;
	int i;

	gig_dbg(DEBUG_CHANNEL, "unblocking all channels");
	spin_lock_irqsave(&cs->lock, flags);
	for (i = 0; i < cs->channels; ++i)
		--cs->bcs[i].use_count;
	spin_unlock_irqrestore(&cs->lock, flags);
}