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
struct bnx2x_raw_obj {int (* wait_comp ) (struct bnx2x*,struct bnx2x_raw_obj*) ;int /*<<< orphan*/  (* clear_pending ) (struct bnx2x_raw_obj*) ;int /*<<< orphan*/  (* set_pending ) (struct bnx2x_raw_obj*) ;} ;
struct bnx2x_rss_config_obj {int (* config_rss ) (struct bnx2x*,struct bnx2x_config_rss_params*) ;struct bnx2x_raw_obj raw; } ;
struct bnx2x_config_rss_params {int /*<<< orphan*/  ramrod_flags; struct bnx2x_rss_config_obj* rss_obj; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  stub1 (struct bnx2x_raw_obj*) ; 
 int stub2 (struct bnx2x*,struct bnx2x_config_rss_params*) ; 
 int /*<<< orphan*/  stub3 (struct bnx2x_raw_obj*) ; 
 int stub4 (struct bnx2x*,struct bnx2x_raw_obj*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2x_config_rss(struct bnx2x *bp,
		     struct bnx2x_config_rss_params *p)
{
	int rc;
	struct bnx2x_rss_config_obj *o = p->rss_obj;
	struct bnx2x_raw_obj *r = &o->raw;

	/* Do nothing if only driver cleanup was requested */
	if (test_bit(RAMROD_DRV_CLR_ONLY, &p->ramrod_flags)) {
		DP(BNX2X_MSG_SP, "Not configuring RSS ramrod_flags=%lx\n",
		   p->ramrod_flags);
		return 0;
	}

	r->set_pending(r);

	rc = o->config_rss(bp, p);
	if (rc < 0) {
		r->clear_pending(r);
		return rc;
	}

	if (test_bit(RAMROD_COMP_WAIT, &p->ramrod_flags))
		rc = r->wait_comp(bp, r);

	return rc;
}