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
struct TYPE_2__ {int num_vcn_inst; int harvest_config; } ;
struct amdgpu_device {int cg_flags; TYPE_1__ vcn; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_VCN_MGCG ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT ; 
 int UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT ; 
 int UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT ; 
 int UVD_CGC_CTRL__IDCT_MODE_MASK ; 
 int UVD_CGC_CTRL__LBSI_MODE_MASK ; 
 int UVD_CGC_CTRL__LMI_MC_MODE_MASK ; 
 int UVD_CGC_CTRL__LMI_UMC_MODE_MASK ; 
 int UVD_CGC_CTRL__LRBBM_MODE_MASK ; 
 int UVD_CGC_CTRL__MPC_MODE_MASK ; 
 int UVD_CGC_CTRL__MPEG2_MODE_MASK ; 
 int UVD_CGC_CTRL__MPRD_MODE_MASK ; 
 int UVD_CGC_CTRL__RBC_MODE_MASK ; 
 int UVD_CGC_CTRL__REGS_MODE_MASK ; 
 int UVD_CGC_CTRL__SYS_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_CM_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_DB_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_IT_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_MP_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_RE_MODE_MASK ; 
 int UVD_CGC_CTRL__VCPU_MODE_MASK ; 
 int UVD_CGC_CTRL__WCB_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__ENT_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__IME_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SCLR_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SCM_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SDB_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SITE_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SIT_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SMP_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SRE_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__UVD_SC_MODE_MASK ; 
 int /*<<< orphan*/  VCN ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmUVD_CGC_CTRL ; 
 int /*<<< orphan*/  mmUVD_SUVD_CGC_CTRL ; 

__attribute__((used)) static void vcn_v2_5_enable_clock_gating(struct amdgpu_device *adev)
{
	uint32_t data = 0;
	int i;

	for (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.harvest_config & (1 << i))
			continue;
		/* enable UVD CGC */
		data = RREG32_SOC15(VCN, i, mmUVD_CGC_CTRL);
		if (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
			data |= 1 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
		else
			data |= 0 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
		data |= 1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
		data |= 4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
		WREG32_SOC15(VCN, i, mmUVD_CGC_CTRL, data);

		data = RREG32_SOC15(VCN, i, mmUVD_CGC_CTRL);
		data |= (UVD_CGC_CTRL__UDEC_RE_MODE_MASK
			| UVD_CGC_CTRL__UDEC_CM_MODE_MASK
			| UVD_CGC_CTRL__UDEC_IT_MODE_MASK
			| UVD_CGC_CTRL__UDEC_DB_MODE_MASK
			| UVD_CGC_CTRL__UDEC_MP_MODE_MASK
			| UVD_CGC_CTRL__SYS_MODE_MASK
			| UVD_CGC_CTRL__UDEC_MODE_MASK
			| UVD_CGC_CTRL__MPEG2_MODE_MASK
			| UVD_CGC_CTRL__REGS_MODE_MASK
			| UVD_CGC_CTRL__RBC_MODE_MASK
			| UVD_CGC_CTRL__LMI_MC_MODE_MASK
			| UVD_CGC_CTRL__LMI_UMC_MODE_MASK
			| UVD_CGC_CTRL__IDCT_MODE_MASK
			| UVD_CGC_CTRL__MPRD_MODE_MASK
			| UVD_CGC_CTRL__MPC_MODE_MASK
			| UVD_CGC_CTRL__LBSI_MODE_MASK
			| UVD_CGC_CTRL__LRBBM_MODE_MASK
			| UVD_CGC_CTRL__WCB_MODE_MASK
			| UVD_CGC_CTRL__VCPU_MODE_MASK);
		WREG32_SOC15(VCN, i, mmUVD_CGC_CTRL, data);

		data = RREG32_SOC15(VCN, i, mmUVD_SUVD_CGC_CTRL);
		data |= (UVD_SUVD_CGC_CTRL__SRE_MODE_MASK
			| UVD_SUVD_CGC_CTRL__SIT_MODE_MASK
			| UVD_SUVD_CGC_CTRL__SMP_MODE_MASK
			| UVD_SUVD_CGC_CTRL__SCM_MODE_MASK
			| UVD_SUVD_CGC_CTRL__SDB_MODE_MASK
			| UVD_SUVD_CGC_CTRL__SCLR_MODE_MASK
			| UVD_SUVD_CGC_CTRL__UVD_SC_MODE_MASK
			| UVD_SUVD_CGC_CTRL__ENT_MODE_MASK
			| UVD_SUVD_CGC_CTRL__IME_MODE_MASK
			| UVD_SUVD_CGC_CTRL__SITE_MODE_MASK);
		WREG32_SOC15(VCN, i, mmUVD_SUVD_CGC_CTRL, data);
	}
}