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
struct cardstate {int commands_pending; int /*<<< orphan*/  dev; } ;
struct bc_state {int proto2; int channel; int /*<<< orphan*/ ** commands; } ;
struct at_state_t {int /*<<< orphan*/  pending_commands; struct cardstate* cs; struct bc_state* bcs; } ;

/* Variables and functions */
 size_t AT_ISO ; 
 int AT_NUM ; 
 size_t AT_PROTO ; 
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PC_ACCEPT ; 
 int /*<<< orphan*/  PC_HUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int) ; 

__attribute__((used)) static void start_accept(struct at_state_t *at_state)
{
	struct cardstate *cs = at_state->cs;
	struct bc_state *bcs = at_state->bcs;
	int i;

	for (i = 0; i < AT_NUM; ++i) {
		kfree(bcs->commands[i]);
		bcs->commands[i] = NULL;
	}

	bcs->commands[AT_PROTO] = kmalloc(9, GFP_ATOMIC);
	bcs->commands[AT_ISO] = kmalloc(9, GFP_ATOMIC);
	if (!bcs->commands[AT_PROTO] || !bcs->commands[AT_ISO]) {
		dev_err(at_state->cs->dev, "out of memory\n");
		/* error reset */
		at_state->pending_commands |= PC_HUP;
		gig_dbg(DEBUG_EVENT, "Scheduling PC_HUP");
		cs->commands_pending = 1;
		return;
	}

	snprintf(bcs->commands[AT_PROTO], 9, "^SBPR=%u\r", bcs->proto2);
	snprintf(bcs->commands[AT_ISO], 9, "^SISO=%u\r", bcs->channel + 1);

	at_state->pending_commands |= PC_ACCEPT;
	gig_dbg(DEBUG_EVENT, "Scheduling PC_ACCEPT");
	cs->commands_pending = 1;
}