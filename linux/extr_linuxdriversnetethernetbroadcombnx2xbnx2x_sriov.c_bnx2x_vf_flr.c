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
struct bnx2x_virtf {int malicious; int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_enable_mbx (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_flr_clnup_hw (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vf_free_resc (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vf_mcast (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bnx2x_vf_queue_flr (struct bnx2x*,struct bnx2x_virtf*,int) ; 
 int vf_rxq_count (struct bnx2x_virtf*) ; 

__attribute__((used)) static void bnx2x_vf_flr(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	int rc, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	/* the cleanup operations are valid if and only if the VF
	 * was first acquired.
	 */
	for (i = 0; i < vf_rxq_count(vf); i++) {
		rc = bnx2x_vf_queue_flr(bp, vf, i);
		if (rc)
			goto out;
	}

	/* remove multicasts */
	bnx2x_vf_mcast(bp, vf, NULL, 0, true);

	/* dispatch final cleanup and wait for HW queues to flush */
	bnx2x_vf_flr_clnup_hw(bp, vf);

	/* release VF resources */
	bnx2x_vf_free_resc(bp, vf);

	vf->malicious = false;

	/* re-open the mailbox */
	bnx2x_vf_enable_mbx(bp, vf->abs_vfid);
	return;
out:
	BNX2X_ERR("vf[%d:%d] failed flr: rc %d\n",
		  vf->abs_vfid, i, rc);
}