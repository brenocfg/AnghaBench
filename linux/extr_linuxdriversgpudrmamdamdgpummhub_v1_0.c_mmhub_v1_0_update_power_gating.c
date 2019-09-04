#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {int pg_flags; TYPE_2__ powerplay; } ;
struct TYPE_3__ {scalar_t__ set_powergating_by_smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_GMC ; 
 int AMD_PG_SUPPORT_MMHUB ; 
 int /*<<< orphan*/  MMHUB ; 
 int /*<<< orphan*/  PCTL0_RENG_EXECUTE ; 
 int /*<<< orphan*/  PCTL1_RENG_EXECUTE ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RENG_EXECUTE_ON_PWR_UP ; 
 int /*<<< orphan*/  RENG_EXECUTE_ON_REG_UPDATE ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_dpm_set_powergating_by_smu (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmPCTL0_RENG_EXECUTE ; 
 int /*<<< orphan*/  mmPCTL1_RENG_EXECUTE ; 

void mmhub_v1_0_update_power_gating(struct amdgpu_device *adev,
				bool enable)
{
	uint32_t pctl0_reng_execute = 0;
	uint32_t pctl1_reng_execute = 0;

	if (amdgpu_sriov_vf(adev))
		return;

	pctl0_reng_execute = RREG32_SOC15(MMHUB, 0, mmPCTL0_RENG_EXECUTE);
	pctl1_reng_execute = RREG32_SOC15(MMHUB, 0, mmPCTL1_RENG_EXECUTE);

	if (enable && adev->pg_flags & AMD_PG_SUPPORT_MMHUB) {
		pctl0_reng_execute = REG_SET_FIELD(pctl0_reng_execute,
						PCTL0_RENG_EXECUTE,
						RENG_EXECUTE_ON_PWR_UP, 1);
		pctl0_reng_execute = REG_SET_FIELD(pctl0_reng_execute,
						PCTL0_RENG_EXECUTE,
						RENG_EXECUTE_ON_REG_UPDATE, 1);
		WREG32_SOC15(MMHUB, 0, mmPCTL0_RENG_EXECUTE, pctl0_reng_execute);

		pctl1_reng_execute = REG_SET_FIELD(pctl1_reng_execute,
						PCTL1_RENG_EXECUTE,
						RENG_EXECUTE_ON_PWR_UP, 1);
		pctl1_reng_execute = REG_SET_FIELD(pctl1_reng_execute,
						PCTL1_RENG_EXECUTE,
						RENG_EXECUTE_ON_REG_UPDATE, 1);
		WREG32_SOC15(MMHUB, 0, mmPCTL1_RENG_EXECUTE, pctl1_reng_execute);

		if (adev->powerplay.pp_funcs->set_powergating_by_smu)
			amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_GMC, true);

	} else {
		pctl0_reng_execute = REG_SET_FIELD(pctl0_reng_execute,
						PCTL0_RENG_EXECUTE,
						RENG_EXECUTE_ON_PWR_UP, 0);
		pctl0_reng_execute = REG_SET_FIELD(pctl0_reng_execute,
						PCTL0_RENG_EXECUTE,
						RENG_EXECUTE_ON_REG_UPDATE, 0);
		WREG32_SOC15(MMHUB, 0, mmPCTL0_RENG_EXECUTE, pctl0_reng_execute);

		pctl1_reng_execute = REG_SET_FIELD(pctl1_reng_execute,
						PCTL1_RENG_EXECUTE,
						RENG_EXECUTE_ON_PWR_UP, 0);
		pctl1_reng_execute = REG_SET_FIELD(pctl1_reng_execute,
						PCTL1_RENG_EXECUTE,
						RENG_EXECUTE_ON_REG_UPDATE, 0);
		WREG32_SOC15(MMHUB, 0, mmPCTL1_RENG_EXECUTE, pctl1_reng_execute);
	}
}