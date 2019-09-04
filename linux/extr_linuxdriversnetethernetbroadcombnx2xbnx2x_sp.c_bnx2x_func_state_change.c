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
struct bnx2x_func_state_params {int cmd; unsigned long ramrod_flags; struct bnx2x_func_sp_obj* f_obj; } ;
struct bnx2x_func_sp_obj {unsigned long pending; int (* check_transition ) (struct bnx2x*,struct bnx2x_func_sp_obj*,struct bnx2x_func_state_params*) ;int (* send_cmd ) (struct bnx2x*,struct bnx2x_func_state_params*) ;int (* wait_comp ) (struct bnx2x*,struct bnx2x_func_sp_obj*,int) ;int /*<<< orphan*/  next_state; int /*<<< orphan*/  one_pending_mutex; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_func_cmd { ____Placeholder_bnx2x_func_cmd } bnx2x_func_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_F_STATE_MAX ; 
 int EBUSY ; 
 int RAMROD_COMP_WAIT ; 
 int RAMROD_DRV_CLR_ONLY ; 
 int RAMROD_RETRY ; 
 int /*<<< orphan*/  bnx2x_func_state_change_comp (struct bnx2x*,struct bnx2x_func_sp_obj*,int) ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int stub1 (struct bnx2x*,struct bnx2x_func_sp_obj*,struct bnx2x_func_state_params*) ; 
 int stub2 (struct bnx2x*,struct bnx2x_func_sp_obj*,struct bnx2x_func_state_params*) ; 
 int stub3 (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int stub4 (struct bnx2x*,struct bnx2x_func_sp_obj*,int) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

int bnx2x_func_state_change(struct bnx2x *bp,
			    struct bnx2x_func_state_params *params)
{
	struct bnx2x_func_sp_obj *o = params->f_obj;
	int rc, cnt = 300;
	enum bnx2x_func_cmd cmd = params->cmd;
	unsigned long *pending = &o->pending;

	mutex_lock(&o->one_pending_mutex);

	/* Check that the requested transition is legal */
	rc = o->check_transition(bp, o, params);
	if ((rc == -EBUSY) &&
	    (test_bit(RAMROD_RETRY, &params->ramrod_flags))) {
		while ((rc == -EBUSY) && (--cnt > 0)) {
			mutex_unlock(&o->one_pending_mutex);
			msleep(10);
			mutex_lock(&o->one_pending_mutex);
			rc = o->check_transition(bp, o, params);
		}
		if (rc == -EBUSY) {
			mutex_unlock(&o->one_pending_mutex);
			BNX2X_ERR("timeout waiting for previous ramrod completion\n");
			return rc;
		}
	} else if (rc) {
		mutex_unlock(&o->one_pending_mutex);
		return rc;
	}

	/* Set "pending" bit */
	set_bit(cmd, pending);

	/* Don't send a command if only driver cleanup was requested */
	if (test_bit(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags)) {
		bnx2x_func_state_change_comp(bp, o, cmd);
		mutex_unlock(&o->one_pending_mutex);
	} else {
		/* Send a ramrod */
		rc = o->send_cmd(bp, params);

		mutex_unlock(&o->one_pending_mutex);

		if (rc) {
			o->next_state = BNX2X_F_STATE_MAX;
			clear_bit(cmd, pending);
			smp_mb__after_atomic();
			return rc;
		}

		if (test_bit(RAMROD_COMP_WAIT, &params->ramrod_flags)) {
			rc = o->wait_comp(bp, o, cmd);
			if (rc)
				return rc;

			return 0;
		}
	}

	return !!test_bit(cmd, pending);
}