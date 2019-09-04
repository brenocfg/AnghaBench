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
 int /*<<< orphan*/  AMD_CG_SUPPORT_BIF_LS ; 
 int /*<<< orphan*/  AMD_CG_SUPPORT_HDP_LS ; 
 int /*<<< orphan*/  AMD_CG_SUPPORT_HDP_MGCG ; 
 int /*<<< orphan*/  AMD_CG_SUPPORT_ROM_MGCG ; 
 int CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK ; 
 int HDP_HOST_PATH_CNTL__CLOCK_GATING_DIS_MASK ; 
 int HDP_MEM_POWER_LS__LS_ENABLE_MASK ; 
 int PCIE_CNTL2__SLV_MEM_LS_EN_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixCGTT_ROM_CLK_CTRL0 ; 
 int /*<<< orphan*/  ixPCIE_CNTL2 ; 
 int /*<<< orphan*/  mmHDP_HOST_PATH_CNTL ; 
 int /*<<< orphan*/  mmHDP_MEM_POWER_LS ; 

__attribute__((used)) static void vi_common_get_clockgating_state(void *handle, u32 *flags)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int data;

	if (amdgpu_sriov_vf(adev))
		*flags = 0;

	/* AMD_CG_SUPPORT_BIF_LS */
	data = RREG32_PCIE(ixPCIE_CNTL2);
	if (data & PCIE_CNTL2__SLV_MEM_LS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_BIF_LS;

	/* AMD_CG_SUPPORT_HDP_LS */
	data = RREG32(mmHDP_MEM_POWER_LS);
	if (data & HDP_MEM_POWER_LS__LS_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_HDP_LS;

	/* AMD_CG_SUPPORT_HDP_MGCG */
	data = RREG32(mmHDP_HOST_PATH_CNTL);
	if (!(data & HDP_HOST_PATH_CNTL__CLOCK_GATING_DIS_MASK))
		*flags |= AMD_CG_SUPPORT_HDP_MGCG;

	/* AMD_CG_SUPPORT_ROM_MGCG */
	data = RREG32_SMC(ixCGTT_ROM_CLK_CTRL0);
	if (!(data & CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK))
		*flags |= AMD_CG_SUPPORT_ROM_MGCG;
}