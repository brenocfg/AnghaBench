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
struct amdgpu_device {scalar_t__ asic_type; int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_MC_MGCG ; 
 int ATC_L2_MISC_CG__ENABLE_MASK ; 
 scalar_t__ CHIP_RAVEN ; 
 int DAGB0_CNTL_MISC2__DISABLE_RDREQ_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_RDRET_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_TLBRD_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_TLBWR_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_WRREQ_CG_MASK ; 
 int DAGB0_CNTL_MISC2__DISABLE_WRRET_CG_MASK ; 
 int DAGB1_CNTL_MISC2__DISABLE_RDREQ_CG_MASK ; 
 int DAGB1_CNTL_MISC2__DISABLE_RDRET_CG_MASK ; 
 int DAGB1_CNTL_MISC2__DISABLE_TLBRD_CG_MASK ; 
 int DAGB1_CNTL_MISC2__DISABLE_TLBWR_CG_MASK ; 
 int DAGB1_CNTL_MISC2__DISABLE_WRREQ_CG_MASK ; 
 int DAGB1_CNTL_MISC2__DISABLE_WRRET_CG_MASK ; 
 int /*<<< orphan*/  MMHUB ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmATC_L2_MISC_CG ; 
 int /*<<< orphan*/  mmDAGB0_CNTL_MISC2 ; 
 int /*<<< orphan*/  mmDAGB0_CNTL_MISC2_RV ; 
 int /*<<< orphan*/  mmDAGB1_CNTL_MISC2 ; 

__attribute__((used)) static void mmhub_v1_0_update_medium_grain_clock_gating(struct amdgpu_device *adev,
							bool enable)
{
	uint32_t def, data, def1, data1, def2 = 0, data2 = 0;

	def  = data  = RREG32_SOC15(MMHUB, 0, mmATC_L2_MISC_CG);

	if (adev->asic_type != CHIP_RAVEN) {
		def1 = data1 = RREG32_SOC15(MMHUB, 0, mmDAGB0_CNTL_MISC2);
		def2 = data2 = RREG32_SOC15(MMHUB, 0, mmDAGB1_CNTL_MISC2);
	} else
		def1 = data1 = RREG32_SOC15(MMHUB, 0, mmDAGB0_CNTL_MISC2_RV);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_MC_MGCG)) {
		data |= ATC_L2_MISC_CG__ENABLE_MASK;

		data1 &= ~(DAGB0_CNTL_MISC2__DISABLE_WRREQ_CG_MASK |
		           DAGB0_CNTL_MISC2__DISABLE_WRRET_CG_MASK |
		           DAGB0_CNTL_MISC2__DISABLE_RDREQ_CG_MASK |
		           DAGB0_CNTL_MISC2__DISABLE_RDRET_CG_MASK |
		           DAGB0_CNTL_MISC2__DISABLE_TLBWR_CG_MASK |
		           DAGB0_CNTL_MISC2__DISABLE_TLBRD_CG_MASK);

		if (adev->asic_type != CHIP_RAVEN)
			data2 &= ~(DAGB1_CNTL_MISC2__DISABLE_WRREQ_CG_MASK |
			           DAGB1_CNTL_MISC2__DISABLE_WRRET_CG_MASK |
			           DAGB1_CNTL_MISC2__DISABLE_RDREQ_CG_MASK |
			           DAGB1_CNTL_MISC2__DISABLE_RDRET_CG_MASK |
			           DAGB1_CNTL_MISC2__DISABLE_TLBWR_CG_MASK |
			           DAGB1_CNTL_MISC2__DISABLE_TLBRD_CG_MASK);
	} else {
		data &= ~ATC_L2_MISC_CG__ENABLE_MASK;

		data1 |= (DAGB0_CNTL_MISC2__DISABLE_WRREQ_CG_MASK |
			  DAGB0_CNTL_MISC2__DISABLE_WRRET_CG_MASK |
			  DAGB0_CNTL_MISC2__DISABLE_RDREQ_CG_MASK |
			  DAGB0_CNTL_MISC2__DISABLE_RDRET_CG_MASK |
			  DAGB0_CNTL_MISC2__DISABLE_TLBWR_CG_MASK |
			  DAGB0_CNTL_MISC2__DISABLE_TLBRD_CG_MASK);

		if (adev->asic_type != CHIP_RAVEN)
			data2 |= (DAGB1_CNTL_MISC2__DISABLE_WRREQ_CG_MASK |
			          DAGB1_CNTL_MISC2__DISABLE_WRRET_CG_MASK |
			          DAGB1_CNTL_MISC2__DISABLE_RDREQ_CG_MASK |
			          DAGB1_CNTL_MISC2__DISABLE_RDRET_CG_MASK |
			          DAGB1_CNTL_MISC2__DISABLE_TLBWR_CG_MASK |
			          DAGB1_CNTL_MISC2__DISABLE_TLBRD_CG_MASK);
	}

	if (def != data)
		WREG32_SOC15(MMHUB, 0, mmATC_L2_MISC_CG, data);

	if (def1 != data1) {
		if (adev->asic_type != CHIP_RAVEN)
			WREG32_SOC15(MMHUB, 0, mmDAGB0_CNTL_MISC2, data1);
		else
			WREG32_SOC15(MMHUB, 0, mmDAGB0_CNTL_MISC2_RV, data1);
	}

	if (adev->asic_type != CHIP_RAVEN && def2 != data2)
		WREG32_SOC15(MMHUB, 0, mmDAGB1_CNTL_MISC2, data2);
}