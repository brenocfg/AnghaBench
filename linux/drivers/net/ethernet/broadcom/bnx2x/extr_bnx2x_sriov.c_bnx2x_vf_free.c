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
struct bnx2x_virtf {int state; int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
#define  VF_ACQUIRED 131 
#define  VF_ENABLED 130 
#define  VF_FREE 129 
#define  VF_RESET 128 
 int bnx2x_vf_close (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vf_free_resc (struct bnx2x*,struct bnx2x_virtf*) ; 

int bnx2x_vf_free(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	int rc;

	DP(BNX2X_MSG_IOV, "VF[%d] STATE: %s\n", vf->abs_vfid,
	   vf->state == VF_FREE ? "Free" :
	   vf->state == VF_ACQUIRED ? "Acquired" :
	   vf->state == VF_ENABLED ? "Enabled" :
	   vf->state == VF_RESET ? "Reset" :
	   "Unknown");

	switch (vf->state) {
	case VF_ENABLED:
		rc = bnx2x_vf_close(bp, vf);
		if (rc)
			goto op_err;
		/* Fall through - to release resources */
	case VF_ACQUIRED:
		DP(BNX2X_MSG_IOV, "about to free resources\n");
		bnx2x_vf_free_resc(bp, vf);
		break;

	case VF_FREE:
	case VF_RESET:
	default:
		break;
	}
	return 0;
op_err:
	BNX2X_ERR("VF[%d] RELEASE error: rc %d\n", vf->abs_vfid, rc);
	return rc;
}