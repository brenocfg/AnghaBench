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
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  CHANNEL_TLV_PF_RELEASE_VF ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_lock_vf_pf_channel (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_unlock_vf_pf_channel (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int bnx2x_vf_free (struct bnx2x*,struct bnx2x_virtf*) ; 

int bnx2x_vf_release(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	int rc;

	DP(BNX2X_MSG_IOV, "PF releasing vf %d\n", vf->abs_vfid);
	bnx2x_lock_vf_pf_channel(bp, vf, CHANNEL_TLV_PF_RELEASE_VF);

	rc = bnx2x_vf_free(bp, vf);
	if (rc)
		WARN(rc,
		     "VF[%d] Failed to allocate resources for release op- rc=%d\n",
		     vf->abs_vfid, rc);
	bnx2x_unlock_vf_pf_channel(bp, vf, CHANNEL_TLV_PF_RELEASE_VF);
	return rc;
}