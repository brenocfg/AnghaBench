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
 int ATCL2_0_ATC_L2_MISC_CG__ENABLE_MASK ; 
 int ATCL2_0_ATC_L2_MISC_CG__MEM_LS_ENABLE_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_RDREQ_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_RDRET_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_TLBRD_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_TLBWR_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_WRREQ_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_WRRET_CG_MASK ; 
 int /*<<< orphan*/  MMHUB ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmATCL2_0_ATC_L2_MISC_CG ; 

void mmhub_v9_4_get_clockgating(struct amdgpu_device *adev, u32 *flags)
{
	int data, data1;

	if (amdgpu_sriov_vf(adev))
		*flags = 0;

	/* AMD_CG_SUPPORT_MC_MGCG */
	data = RREG32_SOC15(MMHUB, 0, mmATCL2_0_ATC_L2_MISC_CG);

	data1 = RREG32_SOC15(MMHUB, 0, mmATCL2_0_ATC_L2_MISC_CG);

	if ((data & ATCL2_0_ATC_L2_MISC_CG__ENABLE_MASK) &&
	    !(data1 & (DAGB0_CNTL_MISC2__DISABLE_WRREQ_CG_MASK |
		       DAGB0_CNTL_MISC2__DISABLE_WRRET_CG_MASK |
		       DAGB0_CNTL_MISC2__DISABLE_RDREQ_CG_MASK |
		       DAGB0_CNTL_MISC2__DISABLE_RDRET_CG_MASK |
		       DAGB0_CNTL_MISC2__DISABLE_TLBWR_CG_MASK |
		       DAGB0_CNTL_MISC2__DISABLE_TLBRD_CG_MASK)))
		*flags |= AMD_CG_SUPPORT_MC_MGCG;

	/* AMD_CG_SUPPORT_MC_LS */
	if (data & ATCL2_0_ATC_L2_MISC_CG__MEM_LS_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_MC_LS;
}