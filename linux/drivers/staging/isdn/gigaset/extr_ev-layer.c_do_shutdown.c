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
struct cardstate {scalar_t__ mstate; int commands_pending; TYPE_1__ at_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 scalar_t__ MS_READY ; 
 scalar_t__ MS_SHUTDOWN ; 
 int /*<<< orphan*/  PC_SHUTDOWN ; 
 int /*<<< orphan*/  finish_shutdown (struct cardstate*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gigaset_block_channels (struct cardstate*) ; 

__attribute__((used)) static void do_shutdown(struct cardstate *cs)
{
	gigaset_block_channels(cs);

	if (cs->mstate == MS_READY) {
		cs->mstate = MS_SHUTDOWN;
		cs->at_state.pending_commands |= PC_SHUTDOWN;
		gig_dbg(DEBUG_EVENT, "Scheduling PC_SHUTDOWN");
		cs->commands_pending = 1;
	} else
		finish_shutdown(cs);
}