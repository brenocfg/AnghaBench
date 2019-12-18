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
typedef  int u32 ;
struct TYPE_5__ {int write_count; int read_count; int* data; int /*<<< orphan*/  lock; int /*<<< orphan*/ * flags; int /*<<< orphan*/ * code; } ;
struct TYPE_6__ {TYPE_2__ vf_errors; TYPE_1__* ops; } ;
struct amdgpu_device {TYPE_3__ virt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* trans_msg ) (struct amdgpu_device*,int /*<<< orphan*/ ,int,int,int) ;} ;

/* Variables and functions */
 int AMDGIM_ERROR_CODE_FLAGS_TO_MAILBOX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int AMDGPU_VF_ERROR_ENTRY_SIZE ; 
 int /*<<< orphan*/  IDH_LOG_VF_ERROR ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int /*<<< orphan*/ ,int,int,int) ; 

void amdgpu_vf_error_trans_all(struct amdgpu_device *adev)
{
	/* u32 pf2vf_flags = 0; */
	u32 data1, data2, data3;
	int index;

	if ((NULL == adev) || (!amdgpu_sriov_vf(adev)) ||
	    (!adev->virt.ops) || (!adev->virt.ops->trans_msg)) {
		return;
	}
/*
 	TODO: Enable these code when pv2vf_info is merged
	AMDGPU_FW_VRAM_PF2VF_READ (adev, feature_flags, &pf2vf_flags);
	if (!(pf2vf_flags & AMDGIM_FEATURE_ERROR_LOG_COLLECT)) {
		return;
	}
*/

	mutex_lock(&adev->virt.vf_errors.lock);
	/* The errors are overlay of array, correct read_count as full. */
	if (adev->virt.vf_errors.write_count - adev->virt.vf_errors.read_count > AMDGPU_VF_ERROR_ENTRY_SIZE) {
		adev->virt.vf_errors.read_count = adev->virt.vf_errors.write_count - AMDGPU_VF_ERROR_ENTRY_SIZE;
	}

	while (adev->virt.vf_errors.read_count < adev->virt.vf_errors.write_count) {
		index =adev->virt.vf_errors.read_count % AMDGPU_VF_ERROR_ENTRY_SIZE;
		data1 = AMDGIM_ERROR_CODE_FLAGS_TO_MAILBOX(adev->virt.vf_errors.code[index],
							   adev->virt.vf_errors.flags[index]);
		data2 = adev->virt.vf_errors.data[index] & 0xFFFFFFFF;
		data3 = (adev->virt.vf_errors.data[index] >> 32) & 0xFFFFFFFF;

		adev->virt.ops->trans_msg(adev, IDH_LOG_VF_ERROR, data1, data2, data3);
		adev->virt.vf_errors.read_count ++;
	}
	mutex_unlock(&adev->virt.vf_errors.lock);
}