#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  scalar_t__ u32 ;
struct amdgpu_vmhub {size_t vm_inv_eng0_req; size_t vm_inv_eng0_ack; } ;
struct TYPE_10__ {int /*<<< orphan*/  invalidate_lock; } ;
struct TYPE_6__ {scalar_t__ ready; } ;
struct TYPE_7__ {TYPE_1__ sched; } ;
struct TYPE_8__ {TYPE_2__ ring; } ;
struct TYPE_9__ {TYPE_3__ kiq; } ;
struct amdgpu_device {size_t num_vmhubs; scalar_t__ usec_timeout; TYPE_5__ gmc; int /*<<< orphan*/  in_gpu_reset; TYPE_4__ gfx; struct amdgpu_vmhub* vmhub; } ;

/* Variables and functions */
 size_t AMDGPU_GFXHUB_0 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ RREG32_NO_KIQ (size_t) ; 
 int /*<<< orphan*/  WREG32_NO_KIQ (size_t,scalar_t__) ; 
 scalar_t__ amdgpu_sriov_runtime (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_virt_kiq_reg_write_reg_wait (struct amdgpu_device*,size_t,size_t,scalar_t__,int) ; 
 scalar_t__ gmc_v9_0_get_invalidate_req (size_t,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gmc_v9_0_flush_gpu_tlb(struct amdgpu_device *adev, uint32_t vmid,
					uint32_t vmhub, uint32_t flush_type)
{
	const unsigned eng = 17;
	u32 j, tmp;
	struct amdgpu_vmhub *hub;

	BUG_ON(vmhub >= adev->num_vmhubs);

	hub = &adev->vmhub[vmhub];
	tmp = gmc_v9_0_get_invalidate_req(vmid, flush_type);

	/* This is necessary for a HW workaround under SRIOV as well
	 * as GFXOFF under bare metal
	 */
	if (adev->gfx.kiq.ring.sched.ready &&
			(amdgpu_sriov_runtime(adev) || !amdgpu_sriov_vf(adev)) &&
			!adev->in_gpu_reset) {
		uint32_t req = hub->vm_inv_eng0_req + eng;
		uint32_t ack = hub->vm_inv_eng0_ack + eng;

		amdgpu_virt_kiq_reg_write_reg_wait(adev, req, ack, tmp,
				1 << vmid);
		return;
	}

	spin_lock(&adev->gmc.invalidate_lock);
	WREG32_NO_KIQ(hub->vm_inv_eng0_req + eng, tmp);

	/*
	 * Issue a dummy read to wait for the ACK register to be cleared
	 * to avoid a false ACK due to the new fast GRBM interface.
	 */
	if (vmhub == AMDGPU_GFXHUB_0)
		RREG32_NO_KIQ(hub->vm_inv_eng0_req + eng);

	for (j = 0; j < adev->usec_timeout; j++) {
		tmp = RREG32_NO_KIQ(hub->vm_inv_eng0_ack + eng);
		if (tmp & (1 << vmid))
			break;
		udelay(1);
	}
	spin_unlock(&adev->gmc.invalidate_lock);
	if (j < adev->usec_timeout)
		return;

	DRM_ERROR("Timeout waiting for VM flush ACK!\n");
}