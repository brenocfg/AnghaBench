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
struct cardstate {int commands_pending; int /*<<< orphan*/  lock; } ;
struct bc_state {char** commands; int /*<<< orphan*/  chstate; } ;
struct at_state_t {unsigned int seq_index; int /*<<< orphan*/  pending_commands; struct cardstate* cs; struct bc_state* bcs; } ;

/* Variables and functions */
 int AT_NUM ; 
 int /*<<< orphan*/  CHS_NOTIFY_LL ; 
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int /*<<< orphan*/  PC_CID ; 
 int /*<<< orphan*/  PC_NOCID ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void start_dial(struct at_state_t *at_state, void *data,
		       unsigned seq_index)
{
	struct bc_state *bcs = at_state->bcs;
	struct cardstate *cs = at_state->cs;
	char **commands = data;
	unsigned long flags;
	int i;

	bcs->chstate |= CHS_NOTIFY_LL;

	spin_lock_irqsave(&cs->lock, flags);
	if (at_state->seq_index != seq_index) {
		spin_unlock_irqrestore(&cs->lock, flags);
		goto error;
	}
	spin_unlock_irqrestore(&cs->lock, flags);

	for (i = 0; i < AT_NUM; ++i) {
		kfree(bcs->commands[i]);
		bcs->commands[i] = commands[i];
	}

	at_state->pending_commands |= PC_CID;
	gig_dbg(DEBUG_EVENT, "Scheduling PC_CID");
	cs->commands_pending = 1;
	return;

error:
	for (i = 0; i < AT_NUM; ++i) {
		kfree(commands[i]);
		commands[i] = NULL;
	}
	at_state->pending_commands |= PC_NOCID;
	gig_dbg(DEBUG_EVENT, "Scheduling PC_NOCID");
	cs->commands_pending = 1;
	return;
}