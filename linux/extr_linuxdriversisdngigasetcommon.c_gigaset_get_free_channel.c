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
struct cardstate {int channels; int /*<<< orphan*/  lock; TYPE_1__* driver; struct bc_state* bcs; } ;
struct bc_state {int busy; int /*<<< orphan*/  use_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CHANNEL ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct bc_state *gigaset_get_free_channel(struct cardstate *cs)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&cs->lock, flags);
	if (!try_module_get(cs->driver->owner)) {
		gig_dbg(DEBUG_CHANNEL,
			"could not get module for allocating channel");
		spin_unlock_irqrestore(&cs->lock, flags);
		return NULL;
	}
	for (i = 0; i < cs->channels; ++i)
		if (!cs->bcs[i].use_count) {
			++cs->bcs[i].use_count;
			cs->bcs[i].busy = 1;
			spin_unlock_irqrestore(&cs->lock, flags);
			gig_dbg(DEBUG_CHANNEL, "allocated channel %d", i);
			return cs->bcs + i;
		}
	module_put(cs->driver->owner);
	spin_unlock_irqrestore(&cs->lock, flags);
	gig_dbg(DEBUG_CHANNEL, "no free channel");
	return NULL;
}