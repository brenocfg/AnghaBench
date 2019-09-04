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
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_DF_MGCG ; 
 int /*<<< orphan*/  DF ; 
 int DF_V3_6_MGCG_ENABLE_15_CYCLE_DELAY ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDF_PIE_AON0_DfGlobalClkGater ; 

__attribute__((used)) static void df_v3_6_get_clockgating_state(struct amdgpu_device *adev,
					  u32 *flags)
{
	u32 tmp;

	/* AMD_CG_SUPPORT_DF_MGCG */
	tmp = RREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater);
	if (tmp & DF_V3_6_MGCG_ENABLE_15_CYCLE_DELAY)
		*flags |= AMD_CG_SUPPORT_DF_MGCG;
}