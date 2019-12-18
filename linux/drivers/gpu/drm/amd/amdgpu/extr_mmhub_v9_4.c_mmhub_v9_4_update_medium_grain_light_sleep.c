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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_MC_LS ; 
 int /*<<< orphan*/  ATCL2_0_ATC_L2_MISC_CG__MEM_LS_ENABLE_MASK ; 
 int /*<<< orphan*/  MMHUB ; 
 int MMHUB_INSTANCE_REGISTER_OFFSET ; 
 int MMHUB_NUM_INSTANCES ; 
 int /*<<< orphan*/  RREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmATCL2_0_ATC_L2_MISC_CG ; 

__attribute__((used)) static void mmhub_v9_4_update_medium_grain_light_sleep(struct amdgpu_device *adev,
						       bool enable)
{
	uint32_t def, data;
	int i;

	for (i = 0; i < MMHUB_NUM_INSTANCES; i++) {
		def = data = RREG32_SOC15_OFFSET(MMHUB, 0,
					mmATCL2_0_ATC_L2_MISC_CG,
					i * MMHUB_INSTANCE_REGISTER_OFFSET);

		if (enable && (adev->cg_flags & AMD_CG_SUPPORT_MC_LS))
			data |= ATCL2_0_ATC_L2_MISC_CG__MEM_LS_ENABLE_MASK;
		else
			data &= ~ATCL2_0_ATC_L2_MISC_CG__MEM_LS_ENABLE_MASK;

		if (def != data)
			WREG32_SOC15_OFFSET(MMHUB, 0, mmATCL2_0_ATC_L2_MISC_CG,
				i * MMHUB_INSTANCE_REGISTER_OFFSET, data);
	}
}