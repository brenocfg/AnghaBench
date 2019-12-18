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
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  BNX2X_VF_FILTER_MAC ; 
 int /*<<< orphan*/  BNX2X_VF_FILTER_VLAN ; 
 int /*<<< orphan*/  BNX2X_VF_FILTER_VLAN_MAC ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int LEADING_IDX ; 
 scalar_t__ bnx2x_validate_vf_sp_objs (struct bnx2x*,struct bnx2x_virtf*,int) ; 
 int bnx2x_vf_mcast (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bnx2x_vf_queue_destroy (struct bnx2x*,struct bnx2x_virtf*,int) ; 
 int bnx2x_vf_rxmode (struct bnx2x*,struct bnx2x_virtf*,int,int /*<<< orphan*/ ) ; 
 int bnx2x_vf_vlan_mac_clear (struct bnx2x*,struct bnx2x_virtf*,int,int,int /*<<< orphan*/ ) ; 

int bnx2x_vf_queue_teardown(struct bnx2x *bp, struct bnx2x_virtf *vf, int qid)
{
	int rc;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->abs_vfid, qid);

	/* Remove all classification configuration for leading queue */
	if (qid == LEADING_IDX) {
		rc = bnx2x_vf_rxmode(bp, vf, qid, 0);
		if (rc)
			goto op_err;

		/* Remove filtering if feasible */
		if (bnx2x_validate_vf_sp_objs(bp, vf, true)) {
			rc = bnx2x_vf_vlan_mac_clear(bp, vf, qid,
						     false,
						     BNX2X_VF_FILTER_VLAN_MAC);
			if (rc)
				goto op_err;
			rc = bnx2x_vf_vlan_mac_clear(bp, vf, qid,
						     false,
						     BNX2X_VF_FILTER_VLAN);
			if (rc)
				goto op_err;
			rc = bnx2x_vf_vlan_mac_clear(bp, vf, qid,
						     false,
						     BNX2X_VF_FILTER_MAC);
			if (rc)
				goto op_err;
			rc = bnx2x_vf_mcast(bp, vf, NULL, 0, false);
			if (rc)
				goto op_err;
		}
	}

	/* Destroy queue */
	rc = bnx2x_vf_queue_destroy(bp, vf, qid);
	if (rc)
		goto op_err;
	return rc;
op_err:
	BNX2X_ERR("vf[%d:%d] error: rc %d\n",
		  vf->abs_vfid, qid, rc);
	return rc;
}