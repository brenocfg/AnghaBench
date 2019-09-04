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
 int EINVAL ; 
 int MC_ARB_BURST_TIME__STATE0_MASK ; 
 int MC_ARB_BURST_TIME__STATE0__SHIFT ; 
 int MC_ARB_BURST_TIME__STATE1_MASK ; 
 int MC_ARB_BURST_TIME__STATE1__SHIFT ; 
 int MC_ARB_CG__CG_ARB_REQ_MASK ; 
 int MC_ARB_CG__CG_ARB_REQ__SHIFT ; 
#define  MC_CG_ARB_FREQ_F0 129 
#define  MC_CG_ARB_FREQ_F1 128 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mmMC_ARB_BURST_TIME ; 
 int /*<<< orphan*/  mmMC_ARB_CG ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING2 ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING2_1 ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING_1 ; 
 int /*<<< orphan*/  mmMC_CG_CONFIG ; 

__attribute__((used)) static int ci_copy_and_switch_arb_sets(struct amdgpu_device *adev,
				       u32 arb_freq_src, u32 arb_freq_dest)
{
	u32 mc_arb_dram_timing;
	u32 mc_arb_dram_timing2;
	u32 burst_time;
	u32 mc_cg_config;

	switch (arb_freq_src) {
	case MC_CG_ARB_FREQ_F0:
		mc_arb_dram_timing  = RREG32(mmMC_ARB_DRAM_TIMING);
		mc_arb_dram_timing2 = RREG32(mmMC_ARB_DRAM_TIMING2);
		burst_time = (RREG32(mmMC_ARB_BURST_TIME) & MC_ARB_BURST_TIME__STATE0_MASK) >>
			 MC_ARB_BURST_TIME__STATE0__SHIFT;
		break;
	case MC_CG_ARB_FREQ_F1:
		mc_arb_dram_timing  = RREG32(mmMC_ARB_DRAM_TIMING_1);
		mc_arb_dram_timing2 = RREG32(mmMC_ARB_DRAM_TIMING2_1);
		burst_time = (RREG32(mmMC_ARB_BURST_TIME) & MC_ARB_BURST_TIME__STATE1_MASK) >>
			 MC_ARB_BURST_TIME__STATE1__SHIFT;
		break;
	default:
		return -EINVAL;
	}

	switch (arb_freq_dest) {
	case MC_CG_ARB_FREQ_F0:
		WREG32(mmMC_ARB_DRAM_TIMING, mc_arb_dram_timing);
		WREG32(mmMC_ARB_DRAM_TIMING2, mc_arb_dram_timing2);
		WREG32_P(mmMC_ARB_BURST_TIME, (burst_time << MC_ARB_BURST_TIME__STATE0__SHIFT),
			~MC_ARB_BURST_TIME__STATE0_MASK);
		break;
	case MC_CG_ARB_FREQ_F1:
		WREG32(mmMC_ARB_DRAM_TIMING_1, mc_arb_dram_timing);
		WREG32(mmMC_ARB_DRAM_TIMING2_1, mc_arb_dram_timing2);
		WREG32_P(mmMC_ARB_BURST_TIME, (burst_time << MC_ARB_BURST_TIME__STATE1__SHIFT),
			~MC_ARB_BURST_TIME__STATE1_MASK);
		break;
	default:
		return -EINVAL;
	}

	mc_cg_config = RREG32(mmMC_CG_CONFIG) | 0x0000000F;
	WREG32(mmMC_CG_CONFIG, mc_cg_config);
	WREG32_P(mmMC_ARB_CG, (arb_freq_dest) << MC_ARB_CG__CG_ARB_REQ__SHIFT,
		~MC_ARB_CG__CG_ARB_REQ_MASK);

	return 0;
}