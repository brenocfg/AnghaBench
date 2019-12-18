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
struct TYPE_2__ {int /*<<< orphan*/  pending_commands; } ;
struct cardstate {int commands_pending; int /*<<< orphan*/  lock; TYPE_1__ at_state; int /*<<< orphan*/  cidmode; } ;
struct at_state_t {int /*<<< orphan*/  list; int /*<<< orphan*/  seq_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int /*<<< orphan*/  PC_UMMODE ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct at_state_t*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void disconnect_nobc(struct at_state_t **at_state_p,
			    struct cardstate *cs)
{
	unsigned long flags;

	spin_lock_irqsave(&cs->lock, flags);
	++(*at_state_p)->seq_index;

	/* revert to selected idle mode */
	if (!cs->cidmode) {
		cs->at_state.pending_commands |= PC_UMMODE;
		gig_dbg(DEBUG_EVENT, "Scheduling PC_UMMODE");
		cs->commands_pending = 1;
	}

	/* check for and deallocate temporary AT state */
	if (!list_empty(&(*at_state_p)->list)) {
		list_del(&(*at_state_p)->list);
		kfree(*at_state_p);
		*at_state_p = NULL;
	}

	spin_unlock_irqrestore(&cs->lock, flags);
}