#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct amdgpu_vmhub {scalar_t__ vm_inv_eng0_ack; scalar_t__ vm_inv_eng0_req; } ;
struct TYPE_2__ {int /*<<< orphan*/  invalidate_lock; } ;
struct amdgpu_device {unsigned int usec_timeout; TYPE_1__ gmc; struct amdgpu_vmhub* vmhub; } ;

/* Variables and functions */
 unsigned int AMDGPU_MAX_VMHUBS ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int RREG32_NO_KIQ (scalar_t__) ; 
 int /*<<< orphan*/  WREG32_NO_KIQ (scalar_t__,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int gmc_v9_0_get_invalidate_req (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gmc_v9_0_flush_gpu_tlb(struct amdgpu_device *adev,
					uint32_t vmid)
{
	/* Use register 17 for GART */
	const unsigned eng = 17;
	unsigned i, j;

	spin_lock(&adev->gmc.invalidate_lock);

	for (i = 0; i < AMDGPU_MAX_VMHUBS; ++i) {
		struct amdgpu_vmhub *hub = &adev->vmhub[i];
		u32 tmp = gmc_v9_0_get_invalidate_req(vmid);

		WREG32_NO_KIQ(hub->vm_inv_eng0_req + eng, tmp);

		/* Busy wait for ACK.*/
		for (j = 0; j < 100; j++) {
			tmp = RREG32_NO_KIQ(hub->vm_inv_eng0_ack + eng);
			tmp &= 1 << vmid;
			if (tmp)
				break;
			cpu_relax();
		}
		if (j < 100)
			continue;

		/* Wait for ACK with a delay.*/
		for (j = 0; j < adev->usec_timeout; j++) {
			tmp = RREG32_NO_KIQ(hub->vm_inv_eng0_ack + eng);
			tmp &= 1 << vmid;
			if (tmp)
				break;
			udelay(1);
		}
		if (j < adev->usec_timeout)
			continue;

		DRM_ERROR("Timeout waiting for VM flush ACK!\n");
	}

	spin_unlock(&adev->gmc.invalidate_lock);
}