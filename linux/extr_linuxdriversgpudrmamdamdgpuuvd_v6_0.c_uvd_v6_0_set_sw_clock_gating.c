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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_GATE_DLY_TIMER ; 
 int /*<<< orphan*/  CLK_OFF_DELAY ; 
 int REG_FIELD_SHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD_CGC_CTRL ; 
 int UVD_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK ; 
 int UVD_CGC_CTRL__CLK_OFF_DELAY_MASK ; 
 int UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK ; 
 int UVD_CGC_CTRL__IDCT_MODE_MASK ; 
 int UVD_CGC_CTRL__JPEG2_MODE_MASK ; 
 int UVD_CGC_CTRL__JPEG_MODE_MASK ; 
 int UVD_CGC_CTRL__LBSI_MODE_MASK ; 
 int UVD_CGC_CTRL__LMI_MC_MODE_MASK ; 
 int UVD_CGC_CTRL__LMI_UMC_MODE_MASK ; 
 int UVD_CGC_CTRL__LRBBM_MODE_MASK ; 
 int UVD_CGC_CTRL__MPC_MODE_MASK ; 
 int UVD_CGC_CTRL__MPEG2_MODE_MASK ; 
 int UVD_CGC_CTRL__MPRD_MODE_MASK ; 
 int UVD_CGC_CTRL__RBC_MODE_MASK ; 
 int UVD_CGC_CTRL__REGS_MODE_MASK ; 
 int UVD_CGC_CTRL__SCPU_MODE_MASK ; 
 int UVD_CGC_CTRL__SYS_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_CM_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_DB_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_IT_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_MP_MODE_MASK ; 
 int UVD_CGC_CTRL__UDEC_RE_MODE_MASK ; 
 int UVD_CGC_CTRL__VCPU_MODE_MASK ; 
 int UVD_CGC_CTRL__WCB_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SCM_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SDB_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SIT_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SMP_MODE_MASK ; 
 int UVD_SUVD_CGC_CTRL__SRE_MODE_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmUVD_CGC_CTRL ; 
 int /*<<< orphan*/  mmUVD_SUVD_CGC_CTRL ; 

__attribute__((used)) static void uvd_v6_0_set_sw_clock_gating(struct amdgpu_device *adev)
{
	uint32_t data, data2;

	data = RREG32(mmUVD_CGC_CTRL);
	data2 = RREG32(mmUVD_SUVD_CGC_CTRL);


	data &= ~(UVD_CGC_CTRL__CLK_OFF_DELAY_MASK |
		  UVD_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK);


	data |= UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK |
		(1 << REG_FIELD_SHIFT(UVD_CGC_CTRL, CLK_GATE_DLY_TIMER)) |
		(4 << REG_FIELD_SHIFT(UVD_CGC_CTRL, CLK_OFF_DELAY));

	data &= ~(UVD_CGC_CTRL__UDEC_RE_MODE_MASK |
			UVD_CGC_CTRL__UDEC_CM_MODE_MASK |
			UVD_CGC_CTRL__UDEC_IT_MODE_MASK |
			UVD_CGC_CTRL__UDEC_DB_MODE_MASK |
			UVD_CGC_CTRL__UDEC_MP_MODE_MASK |
			UVD_CGC_CTRL__SYS_MODE_MASK |
			UVD_CGC_CTRL__UDEC_MODE_MASK |
			UVD_CGC_CTRL__MPEG2_MODE_MASK |
			UVD_CGC_CTRL__REGS_MODE_MASK |
			UVD_CGC_CTRL__RBC_MODE_MASK |
			UVD_CGC_CTRL__LMI_MC_MODE_MASK |
			UVD_CGC_CTRL__LMI_UMC_MODE_MASK |
			UVD_CGC_CTRL__IDCT_MODE_MASK |
			UVD_CGC_CTRL__MPRD_MODE_MASK |
			UVD_CGC_CTRL__MPC_MODE_MASK |
			UVD_CGC_CTRL__LBSI_MODE_MASK |
			UVD_CGC_CTRL__LRBBM_MODE_MASK |
			UVD_CGC_CTRL__WCB_MODE_MASK |
			UVD_CGC_CTRL__VCPU_MODE_MASK |
			UVD_CGC_CTRL__JPEG_MODE_MASK |
			UVD_CGC_CTRL__SCPU_MODE_MASK |
			UVD_CGC_CTRL__JPEG2_MODE_MASK);
	data2 &= ~(UVD_SUVD_CGC_CTRL__SRE_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SIT_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SMP_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SCM_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SDB_MODE_MASK);

	WREG32(mmUVD_CGC_CTRL, data);
	WREG32(mmUVD_SUVD_CGC_CTRL, data2);
}