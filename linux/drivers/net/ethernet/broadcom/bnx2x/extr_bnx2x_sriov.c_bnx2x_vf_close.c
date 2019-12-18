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
struct set_vf_state_cookie {int /*<<< orphan*/  state; struct bnx2x_virtf* vf; } ;
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  VF_ACQUIRED ; 
 int /*<<< orphan*/  bnx2x_set_vf_state ; 
 int bnx2x_stats_safe_exec (struct bnx2x*,int /*<<< orphan*/ ,struct set_vf_state_cookie*) ; 
 int /*<<< orphan*/  bnx2x_vf_clr_qtbl (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vf_igu_disable (struct bnx2x*,struct bnx2x_virtf*) ; 
 int bnx2x_vf_queue_teardown (struct bnx2x*,struct bnx2x_virtf*,int) ; 
 int vf_rxq_count (struct bnx2x_virtf*) ; 

int bnx2x_vf_close(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	int rc = 0, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	/* Close all queues */
	for (i = 0; i < vf_rxq_count(vf); i++) {
		rc = bnx2x_vf_queue_teardown(bp, vf, i);
		if (rc)
			goto op_err;
	}

	/* disable the interrupts */
	DP(BNX2X_MSG_IOV, "disabling igu\n");
	bnx2x_vf_igu_disable(bp, vf);

	/* disable the VF */
	DP(BNX2X_MSG_IOV, "clearing qtbl\n");
	bnx2x_vf_clr_qtbl(bp, vf);

	/* need to make sure there are no outstanding stats ramrods which may
	 * cause the device to access the VF's stats buffer which it will free
	 * as soon as we return from the close flow.
	 */
	{
		struct set_vf_state_cookie cookie;

		cookie.vf = vf;
		cookie.state = VF_ACQUIRED;
		rc = bnx2x_stats_safe_exec(bp, bnx2x_set_vf_state, &cookie);
		if (rc)
			goto op_err;
	}

	DP(BNX2X_MSG_IOV, "set state to acquired\n");

	return 0;
op_err:
	BNX2X_ERR("vf[%d] CLOSE error: rc %d\n", vf->abs_vfid, rc);
	return rc;
}