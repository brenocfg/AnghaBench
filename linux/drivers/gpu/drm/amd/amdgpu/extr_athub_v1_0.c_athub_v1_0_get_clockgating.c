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
 int /*<<< orphan*/  AMD_CG_SUPPORT_ATHUB_LS ; 
 int /*<<< orphan*/  AMD_CG_SUPPORT_ATHUB_MGCG ; 
 int /*<<< orphan*/  ATHUB ; 
 int ATHUB_MISC_CNTL__CG_ENABLE_MASK ; 
 int ATHUB_MISC_CNTL__CG_MEM_LS_ENABLE_MASK ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmATHUB_MISC_CNTL ; 

void athub_v1_0_get_clockgating(struct amdgpu_device *adev, u32 *flags)
{
	int data;

	if (amdgpu_sriov_vf(adev))
		*flags = 0;

	/* AMD_CG_SUPPORT_ATHUB_MGCG */
	data = RREG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTL);
	if (data & ATHUB_MISC_CNTL__CG_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_ATHUB_MGCG;

	/* AMD_CG_SUPPORT_ATHUB_LS */
	if (data & ATHUB_MISC_CNTL__CG_MEM_LS_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_ATHUB_LS;
}