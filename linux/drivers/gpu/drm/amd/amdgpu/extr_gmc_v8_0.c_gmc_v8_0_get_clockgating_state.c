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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_SUPPORT_MC_LS ; 
 int /*<<< orphan*/  AMD_CG_SUPPORT_MC_MGCG ; 
 int MC_HUB_MISC_HUB_CG__ENABLE_MASK ; 
 int MC_HUB_MISC_HUB_CG__MEM_LS_ENABLE_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmMC_HUB_MISC_HUB_CG ; 

__attribute__((used)) static void gmc_v8_0_get_clockgating_state(void *handle, u32 *flags)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int data;

	if (amdgpu_sriov_vf(adev))
		*flags = 0;

	/* AMD_CG_SUPPORT_MC_MGCG */
	data = RREG32(mmMC_HUB_MISC_HUB_CG);
	if (data & MC_HUB_MISC_HUB_CG__ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_MC_MGCG;

	/* AMD_CG_SUPPORT_MC_LS */
	if (data & MC_HUB_MISC_HUB_CG__MEM_LS_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_MC_LS;
}