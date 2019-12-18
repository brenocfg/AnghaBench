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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int cg_flags; TYPE_1__* df_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_broadcast_mode ) (struct amdgpu_device*,int) ;} ;

/* Variables and functions */
 int AMD_CG_SUPPORT_DF_MGCG ; 
 int /*<<< orphan*/  DF ; 
 int /*<<< orphan*/  DF_PIE_AON0_DfGlobalClkGater__MGCGMode_MASK ; 
 int /*<<< orphan*/  DF_V1_7_MGCG_DISABLE ; 
 int /*<<< orphan*/  DF_V1_7_MGCG_ENABLE_15_CYCLE_DELAY ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDF_PIE_AON0_DfGlobalClkGater ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*,int) ; 

__attribute__((used)) static void df_v1_7_update_medium_grain_clock_gating(struct amdgpu_device *adev,
						     bool enable)
{
	u32 tmp;

	/* Put DF on broadcast mode */
	adev->df_funcs->enable_broadcast_mode(adev, true);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_DF_MGCG)) {
		tmp = RREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater);
		tmp &= ~DF_PIE_AON0_DfGlobalClkGater__MGCGMode_MASK;
		tmp |= DF_V1_7_MGCG_ENABLE_15_CYCLE_DELAY;
		WREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater, tmp);
	} else {
		tmp = RREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater);
		tmp &= ~DF_PIE_AON0_DfGlobalClkGater__MGCGMode_MASK;
		tmp |= DF_V1_7_MGCG_DISABLE;
		WREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater, tmp);
	}

	/* Exit boradcast mode */
	adev->df_funcs->enable_broadcast_mode(adev, false);
}