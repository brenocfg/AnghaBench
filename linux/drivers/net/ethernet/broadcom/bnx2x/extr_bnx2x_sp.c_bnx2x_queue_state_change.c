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
struct bnx2x_queue_state_params {unsigned long ramrod_flags; struct bnx2x_queue_sp_obj* q_obj; } ;
struct bnx2x_queue_sp_obj {unsigned long pending; int (* check_transition ) (struct bnx2x*,struct bnx2x_queue_sp_obj*,struct bnx2x_queue_state_params*) ;int (* set_pending ) (struct bnx2x_queue_sp_obj*,struct bnx2x_queue_state_params*) ;int (* send_cmd ) (struct bnx2x*,struct bnx2x_queue_state_params*) ;int (* wait_comp ) (struct bnx2x*,struct bnx2x_queue_sp_obj*,int) ;int /*<<< orphan*/  next_state; int /*<<< orphan*/  (* complete_cmd ) (struct bnx2x*,struct bnx2x_queue_sp_obj*,int) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BNX2X_Q_STATE_MAX ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int EINVAL ; 
 int RAMROD_COMP_WAIT ; 
 int RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int stub1 (struct bnx2x*,struct bnx2x_queue_sp_obj*,struct bnx2x_queue_state_params*) ; 
 int stub2 (struct bnx2x_queue_sp_obj*,struct bnx2x_queue_state_params*) ; 
 int /*<<< orphan*/  stub3 (struct bnx2x*,struct bnx2x_queue_sp_obj*,int) ; 
 int stub4 (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int stub5 (struct bnx2x*,struct bnx2x_queue_sp_obj*,int) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

int bnx2x_queue_state_change(struct bnx2x *bp,
			     struct bnx2x_queue_state_params *params)
{
	struct bnx2x_queue_sp_obj *o = params->q_obj;
	int rc, pending_bit;
	unsigned long *pending = &o->pending;

	/* Check that the requested transition is legal */
	rc = o->check_transition(bp, o, params);
	if (rc) {
		BNX2X_ERR("check transition returned an error. rc %d\n", rc);
		return -EINVAL;
	}

	/* Set "pending" bit */
	DP(BNX2X_MSG_SP, "pending bit was=%lx\n", o->pending);
	pending_bit = o->set_pending(o, params);
	DP(BNX2X_MSG_SP, "pending bit now=%lx\n", o->pending);

	/* Don't send a command if only driver cleanup was requested */
	if (test_bit(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags))
		o->complete_cmd(bp, o, pending_bit);
	else {
		/* Send a ramrod */
		rc = o->send_cmd(bp, params);
		if (rc) {
			o->next_state = BNX2X_Q_STATE_MAX;
			clear_bit(pending_bit, pending);
			smp_mb__after_atomic();
			return rc;
		}

		if (test_bit(RAMROD_COMP_WAIT, &params->ramrod_flags)) {
			rc = o->wait_comp(bp, o, pending_bit);
			if (rc)
				return rc;

			return 0;
		}
	}

	return !!test_bit(pending_bit, pending);
}