#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pvr2_context {TYPE_2__* mc_first; TYPE_1__* mc_last; } ;
struct pvr2_channel {int /*<<< orphan*/ * hdw; TYPE_2__* mc_next; TYPE_1__* mc_prev; scalar_t__ input_mask; struct pvr2_context* mc_head; } ;
struct TYPE_4__ {TYPE_1__* mc_prev; } ;
struct TYPE_3__ {TYPE_2__* mc_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  pvr2_channel_disclaim_stream (struct pvr2_channel*) ; 
 int /*<<< orphan*/  pvr2_context_enter (struct pvr2_context*) ; 
 int /*<<< orphan*/  pvr2_context_exit (struct pvr2_context*) ; 
 int /*<<< orphan*/  pvr2_context_reset_input_limits (struct pvr2_context*) ; 

void pvr2_channel_done(struct pvr2_channel *cp)
{
	struct pvr2_context *mp = cp->mc_head;
	pvr2_context_enter(mp);
	cp->input_mask = 0;
	pvr2_channel_disclaim_stream(cp);
	pvr2_context_reset_input_limits(mp);
	if (cp->mc_next) {
		cp->mc_next->mc_prev = cp->mc_prev;
	} else {
		mp->mc_last = cp->mc_prev;
	}
	if (cp->mc_prev) {
		cp->mc_prev->mc_next = cp->mc_next;
	} else {
		mp->mc_first = cp->mc_next;
	}
	cp->hdw = NULL;
	pvr2_context_exit(mp);
}