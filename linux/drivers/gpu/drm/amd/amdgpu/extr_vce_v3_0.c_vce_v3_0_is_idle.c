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
typedef  int u32 ;
struct TYPE_2__ {int harvest_config; } ;
struct amdgpu_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int AMDGPU_VCE_HARVEST_VCE0 ; 
 int AMDGPU_VCE_HARVEST_VCE1 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SRBM_STATUS2__VCE0_BUSY_MASK ; 
 int SRBM_STATUS2__VCE1_BUSY_MASK ; 
 int /*<<< orphan*/  mmSRBM_STATUS2 ; 

__attribute__((used)) static bool vce_v3_0_is_idle(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 mask = 0;

	mask |= (adev->vce.harvest_config & AMDGPU_VCE_HARVEST_VCE0) ? 0 : SRBM_STATUS2__VCE0_BUSY_MASK;
	mask |= (adev->vce.harvest_config & AMDGPU_VCE_HARVEST_VCE1) ? 0 : SRBM_STATUS2__VCE1_BUSY_MASK;

	return !(RREG32(mmSRBM_STATUS2) & mask);
}