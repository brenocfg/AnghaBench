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
typedef  int uint32_t ;
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_MC_MGCG ; 
 int ATCL2_0_ATC_L2_MISC_CG__ENABLE_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_RDREQ_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_RDRET_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_TLBRD_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_TLBWR_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_WRREQ_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_WRRET_CG_MASK ; 
 int /*<<< orphan*/  MMHUB ; 
 int MMHUB_INSTANCE_REGISTER_OFFSET ; 
 int MMHUB_NUM_INSTANCES ; 
 int RREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int mmATCL2_0_ATC_L2_MISC_CG ; 
 int mmDAGB0_CNTL_MISC2 ; 
 int mmDAGB1_CNTL_MISC2 ; 

__attribute__((used)) static void mmhub_v9_4_update_medium_grain_clock_gating(struct amdgpu_device *adev,
							bool enable)
{
	uint32_t def, data, def1, data1;
	int i, j;
	int dist = mmDAGB1_CNTL_MISC2 - mmDAGB0_CNTL_MISC2;

	for (i = 0; i < MMHUB_NUM_INSTANCES; i++) {
		def = data = RREG32_SOC15_OFFSET(MMHUB, 0,
					mmATCL2_0_ATC_L2_MISC_CG,
					i * MMHUB_INSTANCE_REGISTER_OFFSET);

		if (enable && (adev->cg_flags & AMD_CG_SUPPORT_MC_MGCG))
			data |= ATCL2_0_ATC_L2_MISC_CG__ENABLE_MASK;
		else
			data &= ~ATCL2_0_ATC_L2_MISC_CG__ENABLE_MASK;

		if (def != data)
			WREG32_SOC15_OFFSET(MMHUB, 0, mmATCL2_0_ATC_L2_MISC_CG,
				i * MMHUB_INSTANCE_REGISTER_OFFSET, data);

		for (j = 0; j < 5; j++) {
			def1 = data1 = RREG32_SOC15_OFFSET(MMHUB, 0,
					mmDAGB0_CNTL_MISC2,
					i * MMHUB_INSTANCE_REGISTER_OFFSET +
					j * dist);
			if (enable &&
			    (adev->cg_flags & AMD_CG_SUPPORT_MC_MGCG)) {
				data1 &=
				    ~(DAGB0_CNTL_MISC2__DISABLE_WRREQ_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_WRRET_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_RDREQ_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_RDRET_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_TLBWR_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_TLBRD_CG_MASK);
			} else {
				data1 |=
				    (DAGB0_CNTL_MISC2__DISABLE_WRREQ_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_WRRET_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_RDREQ_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_RDRET_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_TLBWR_CG_MASK |
				    DAGB0_CNTL_MISC2__DISABLE_TLBRD_CG_MASK);
			}

			if (def1 != data1)
				WREG32_SOC15_OFFSET(MMHUB, 0,
					mmDAGB0_CNTL_MISC2,
					i * MMHUB_INSTANCE_REGISTER_OFFSET +
					j * dist, data1);

			if (i == 1 && j == 3)
				break;
		}
	}
}