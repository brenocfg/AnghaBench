#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u8 ;
struct vf_pf_event_data {scalar_t__ vf_id; int /*<<< orphan*/  msg_addr_lo; int /*<<< orphan*/  msg_addr_hi; } ;
struct bnx2x {int dummy; } ;
struct TYPE_4__ {scalar_t__ first_vf_in_pf; } ;
struct TYPE_6__ {unsigned long long event_occur; int /*<<< orphan*/  event_mutex; TYPE_1__ sriov; } ;
struct TYPE_5__ {void* vf_addr_lo; void* vf_addr_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_IOV_HANDLE_VF_MSG ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 scalar_t__ BNX2X_NR_VIRTFN (struct bnx2x*) ; 
 TYPE_3__* BP_VFDB (struct bnx2x*) ; 
 TYPE_2__* BP_VF_MBX (struct bnx2x*,unsigned long long) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_schedule_iov_task (struct bnx2x*,int /*<<< orphan*/ ) ; 
 unsigned long long bnx2x_vf_idx_by_abs_fid (struct bnx2x*,scalar_t__) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void bnx2x_vf_mbx_schedule(struct bnx2x *bp,
			   struct vf_pf_event_data *vfpf_event)
{
	u8 vf_idx;

	DP(BNX2X_MSG_IOV,
	   "vf pf event received: vfid %d, address_hi %x, address lo %x",
	   vfpf_event->vf_id, vfpf_event->msg_addr_hi, vfpf_event->msg_addr_lo);
	/* Sanity checks consider removing later */

	/* check if the vf_id is valid */
	if (vfpf_event->vf_id - BP_VFDB(bp)->sriov.first_vf_in_pf >
	    BNX2X_NR_VIRTFN(bp)) {
		BNX2X_ERR("Illegal vf_id %d max allowed: %d\n",
			  vfpf_event->vf_id, BNX2X_NR_VIRTFN(bp));
		return;
	}

	vf_idx = bnx2x_vf_idx_by_abs_fid(bp, vfpf_event->vf_id);

	/* Update VFDB with current message and schedule its handling */
	mutex_lock(&BP_VFDB(bp)->event_mutex);
	BP_VF_MBX(bp, vf_idx)->vf_addr_hi =
		le32_to_cpu(vfpf_event->msg_addr_hi);
	BP_VF_MBX(bp, vf_idx)->vf_addr_lo =
		le32_to_cpu(vfpf_event->msg_addr_lo);
	BP_VFDB(bp)->event_occur |= (1ULL << vf_idx);
	mutex_unlock(&BP_VFDB(bp)->event_mutex);

	bnx2x_schedule_iov_task(bp, BNX2X_IOV_HANDLE_VF_MSG);
}