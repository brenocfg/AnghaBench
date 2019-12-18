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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {TYPE_1__* nbio_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_clockgating_state ) (struct amdgpu_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_SUPPORT_HDP_DS ; 
 int /*<<< orphan*/  AMD_CG_SUPPORT_HDP_LS ; 
 int /*<<< orphan*/  AMD_CG_SUPPORT_HDP_MGCG ; 
 int /*<<< orphan*/  AMD_CG_SUPPORT_HDP_SD ; 
 int /*<<< orphan*/  HDP ; 
 int HDP_CLK_CNTL__DBUS_CLK_SOFT_OVERRIDE_MASK ; 
 int HDP_CLK_CNTL__DYN_CLK_SOFT_OVERRIDE_MASK ; 
 int HDP_CLK_CNTL__HDP_REG_CLK_SOFT_OVERRIDE_MASK ; 
 int HDP_CLK_CNTL__IPH_MEM_CLK_SOFT_OVERRIDE_MASK ; 
 int HDP_CLK_CNTL__RC_MEM_CLK_SOFT_OVERRIDE_MASK ; 
 int HDP_CLK_CNTL__XDP_REG_CLK_SOFT_OVERRIDE_MASK ; 
 int HDP_MEM_POWER_CTRL__IPH_MEM_POWER_DS_EN_MASK ; 
 int HDP_MEM_POWER_CTRL__IPH_MEM_POWER_LS_EN_MASK ; 
 int HDP_MEM_POWER_CTRL__IPH_MEM_POWER_SD_EN_MASK ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmHDP_CLK_CNTL ; 
 int /*<<< orphan*/  mmHDP_MEM_POWER_CTRL ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nv_common_get_clockgating_state(void *handle, u32 *flags)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	uint32_t tmp;

	if (amdgpu_sriov_vf(adev))
		*flags = 0;

	adev->nbio_funcs->get_clockgating_state(adev, flags);

	/* AMD_CG_SUPPORT_HDP_MGCG */
	tmp = RREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL);
	if (!(tmp & (HDP_CLK_CNTL__IPH_MEM_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__RC_MEM_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__DBUS_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__DYN_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__XDP_REG_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__HDP_REG_CLK_SOFT_OVERRIDE_MASK)))
		*flags |= AMD_CG_SUPPORT_HDP_MGCG;

	/* AMD_CG_SUPPORT_HDP_LS/DS/SD */
	tmp = RREG32_SOC15(HDP, 0, mmHDP_MEM_POWER_CTRL);
	if (tmp & HDP_MEM_POWER_CTRL__IPH_MEM_POWER_LS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_HDP_LS;
	else if (tmp & HDP_MEM_POWER_CTRL__IPH_MEM_POWER_DS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_HDP_DS;
	else if (tmp & HDP_MEM_POWER_CTRL__IPH_MEM_POWER_SD_EN_MASK)
		*flags |= AMD_CG_SUPPORT_HDP_SD;

	return;
}