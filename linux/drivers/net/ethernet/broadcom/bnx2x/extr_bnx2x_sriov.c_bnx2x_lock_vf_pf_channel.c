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
struct bnx2x_virtf {int op_current; int /*<<< orphan*/  abs_vfid; int /*<<< orphan*/  op_mutex; } ;
struct bnx2x {int dummy; } ;
typedef  enum channel_tlvs { ____Placeholder_channel_tlvs } channel_tlvs ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_tlv_supported (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

void bnx2x_lock_vf_pf_channel(struct bnx2x *bp, struct bnx2x_virtf *vf,
			      enum channel_tlvs tlv)
{
	/* we don't lock the channel for unsupported tlvs */
	if (!bnx2x_tlv_supported(tlv)) {
		BNX2X_ERR("attempting to lock with unsupported tlv. Aborting\n");
		return;
	}

	/* lock the channel */
	mutex_lock(&vf->op_mutex);

	/* record the locking op */
	vf->op_current = tlv;

	/* log the lock */
	DP(BNX2X_MSG_IOV, "VF[%d]: vf pf channel locked by %d\n",
	   vf->abs_vfid, tlv);
}