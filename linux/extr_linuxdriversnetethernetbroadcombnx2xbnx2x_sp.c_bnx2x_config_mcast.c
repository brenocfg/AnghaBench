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
struct bnx2x_raw_obj {int /*<<< orphan*/  (* clear_pending ) (struct bnx2x_raw_obj*) ;int /*<<< orphan*/  (* set_pending ) (struct bnx2x_raw_obj*) ;scalar_t__ (* check_pending ) (struct bnx2x_raw_obj*) ;} ;
struct bnx2x_mcast_ramrod_params {int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/  mcast_list_len; struct bnx2x_mcast_obj* mcast_obj; } ;
struct bnx2x_mcast_obj {int (* get_registry_size ) (struct bnx2x_mcast_obj*) ;int (* validate ) (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int) ;scalar_t__ total_pending_num; scalar_t__ max_cmd_len; int (* enqueue_cmd ) (struct bnx2x*,struct bnx2x_mcast_obj*,struct bnx2x_mcast_ramrod_params*,int) ;int (* config_mcast ) (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int) ;int (* wait_comp ) (struct bnx2x*,struct bnx2x_mcast_obj*) ;int /*<<< orphan*/  (* revert ) (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int,int) ;int /*<<< orphan*/  (* check_sched ) (struct bnx2x_mcast_obj*) ;struct bnx2x_raw_obj raw; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_mcast_cmd { ____Placeholder_bnx2x_mcast_cmd } bnx2x_mcast_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int stub1 (struct bnx2x_mcast_obj*) ; 
 int /*<<< orphan*/  stub10 (struct bnx2x_raw_obj*) ; 
 int /*<<< orphan*/  stub11 (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int,int) ; 
 int stub2 (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int) ; 
 int /*<<< orphan*/  stub3 (struct bnx2x_mcast_obj*) ; 
 scalar_t__ stub4 (struct bnx2x_raw_obj*) ; 
 int stub5 (struct bnx2x*,struct bnx2x_mcast_obj*,struct bnx2x_mcast_ramrod_params*,int) ; 
 scalar_t__ stub6 (struct bnx2x_raw_obj*) ; 
 int /*<<< orphan*/  stub7 (struct bnx2x_raw_obj*) ; 
 int stub8 (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int) ; 
 int stub9 (struct bnx2x*,struct bnx2x_mcast_obj*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2x_config_mcast(struct bnx2x *bp,
		       struct bnx2x_mcast_ramrod_params *p,
		       enum bnx2x_mcast_cmd cmd)
{
	struct bnx2x_mcast_obj *o = p->mcast_obj;
	struct bnx2x_raw_obj *r = &o->raw;
	int rc = 0, old_reg_size;

	/* This is needed to recover number of currently configured mcast macs
	 * in case of failure.
	 */
	old_reg_size = o->get_registry_size(o);

	/* Do some calculations and checks */
	rc = o->validate(bp, p, cmd);
	if (rc)
		return rc;

	/* Return if there is no work to do */
	if ((!p->mcast_list_len) && (!o->check_sched(o)))
		return 0;

	DP(BNX2X_MSG_SP, "o->total_pending_num=%d p->mcast_list_len=%d o->max_cmd_len=%d\n",
	   o->total_pending_num, p->mcast_list_len, o->max_cmd_len);

	/* Enqueue the current command to the pending list if we can't complete
	 * it in the current iteration
	 */
	if (r->check_pending(r) ||
	    ((o->max_cmd_len > 0) && (o->total_pending_num > o->max_cmd_len))) {
		rc = o->enqueue_cmd(bp, p->mcast_obj, p, cmd);
		if (rc < 0)
			goto error_exit1;

		/* As long as the current command is in a command list we
		 * don't need to handle it separately.
		 */
		p->mcast_list_len = 0;
	}

	if (!r->check_pending(r)) {

		/* Set 'pending' state */
		r->set_pending(r);

		/* Configure the new classification in the chip */
		rc = o->config_mcast(bp, p, cmd);
		if (rc < 0)
			goto error_exit2;

		/* Wait for a ramrod completion if was requested */
		if (test_bit(RAMROD_COMP_WAIT, &p->ramrod_flags))
			rc = o->wait_comp(bp, o);
	}

	return rc;

error_exit2:
	r->clear_pending(r);

error_exit1:
	o->revert(bp, p, old_reg_size, cmd);

	return rc;
}