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
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_UVD ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int UVD_CGC_GATE__IDCT_MASK ; 
 int UVD_CGC_GATE__JPEG2_MASK ; 
 int UVD_CGC_GATE__JPEG_MASK ; 
 int UVD_CGC_GATE__LBSI_MASK ; 
 int UVD_CGC_GATE__LMI_MC_MASK ; 
 int UVD_CGC_GATE__LMI_UMC_MASK ; 
 int UVD_CGC_GATE__LRBBM_MASK ; 
 int UVD_CGC_GATE__MPC_MASK ; 
 int UVD_CGC_GATE__MPEG2_MASK ; 
 int UVD_CGC_GATE__MPRD_MASK ; 
 int UVD_CGC_GATE__RBC_MASK ; 
 int UVD_CGC_GATE__REGS_MASK ; 
 int UVD_CGC_GATE__SCPU_MASK ; 
 int UVD_CGC_GATE__SYS_MASK ; 
 int UVD_CGC_GATE__UDEC_CM_MASK ; 
 int UVD_CGC_GATE__UDEC_DB_MASK ; 
 int UVD_CGC_GATE__UDEC_IT_MASK ; 
 int UVD_CGC_GATE__UDEC_MASK ; 
 int UVD_CGC_GATE__UDEC_MP_MASK ; 
 int UVD_CGC_GATE__UDEC_RE_MASK ; 
 int UVD_CGC_GATE__VCPU_MASK ; 
 int UVD_CGC_GATE__WCB_MASK ; 
 int UVD_SUVD_CGC_GATE__SCM_H264_MASK ; 
 int UVD_SUVD_CGC_GATE__SCM_HEVC_MASK ; 
 int UVD_SUVD_CGC_GATE__SCM_MASK ; 
 int UVD_SUVD_CGC_GATE__SDB_H264_MASK ; 
 int UVD_SUVD_CGC_GATE__SDB_HEVC_MASK ; 
 int UVD_SUVD_CGC_GATE__SDB_MASK ; 
 int UVD_SUVD_CGC_GATE__SIT_H264_MASK ; 
 int UVD_SUVD_CGC_GATE__SIT_HEVC_MASK ; 
 int UVD_SUVD_CGC_GATE__SIT_MASK ; 
 int UVD_SUVD_CGC_GATE__SMP_MASK ; 
 int UVD_SUVD_CGC_GATE__SRE_H264_MASK ; 
 int UVD_SUVD_CGC_GATE__SRE_HEVC_MASK ; 
 int UVD_SUVD_CGC_GATE__SRE_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmUVD_CGC_GATE ; 
 int /*<<< orphan*/  mmUVD_SUVD_CGC_GATE ; 

__attribute__((used)) static void uvd_v6_0_enable_clock_gating(struct amdgpu_device *adev, bool enable)
{
	uint32_t data1, data3;

	data1 = RREG32(mmUVD_SUVD_CGC_GATE);
	data3 = RREG32(mmUVD_CGC_GATE);

	data1 |= UVD_SUVD_CGC_GATE__SRE_MASK |
		     UVD_SUVD_CGC_GATE__SIT_MASK |
		     UVD_SUVD_CGC_GATE__SMP_MASK |
		     UVD_SUVD_CGC_GATE__SCM_MASK |
		     UVD_SUVD_CGC_GATE__SDB_MASK |
		     UVD_SUVD_CGC_GATE__SRE_H264_MASK |
		     UVD_SUVD_CGC_GATE__SRE_HEVC_MASK |
		     UVD_SUVD_CGC_GATE__SIT_H264_MASK |
		     UVD_SUVD_CGC_GATE__SIT_HEVC_MASK |
		     UVD_SUVD_CGC_GATE__SCM_H264_MASK |
		     UVD_SUVD_CGC_GATE__SCM_HEVC_MASK |
		     UVD_SUVD_CGC_GATE__SDB_H264_MASK |
		     UVD_SUVD_CGC_GATE__SDB_HEVC_MASK;

	if (enable) {
		data3 |= (UVD_CGC_GATE__SYS_MASK       |
			UVD_CGC_GATE__UDEC_MASK      |
			UVD_CGC_GATE__MPEG2_MASK     |
			UVD_CGC_GATE__RBC_MASK       |
			UVD_CGC_GATE__LMI_MC_MASK    |
			UVD_CGC_GATE__LMI_UMC_MASK   |
			UVD_CGC_GATE__IDCT_MASK      |
			UVD_CGC_GATE__MPRD_MASK      |
			UVD_CGC_GATE__MPC_MASK       |
			UVD_CGC_GATE__LBSI_MASK      |
			UVD_CGC_GATE__LRBBM_MASK     |
			UVD_CGC_GATE__UDEC_RE_MASK   |
			UVD_CGC_GATE__UDEC_CM_MASK   |
			UVD_CGC_GATE__UDEC_IT_MASK   |
			UVD_CGC_GATE__UDEC_DB_MASK   |
			UVD_CGC_GATE__UDEC_MP_MASK   |
			UVD_CGC_GATE__WCB_MASK       |
			UVD_CGC_GATE__JPEG_MASK      |
			UVD_CGC_GATE__SCPU_MASK      |
			UVD_CGC_GATE__JPEG2_MASK);
		/* only in pg enabled, we can gate clock to vcpu*/
		if (adev->pg_flags & AMD_PG_SUPPORT_UVD)
			data3 |= UVD_CGC_GATE__VCPU_MASK;

		data3 &= ~UVD_CGC_GATE__REGS_MASK;
	} else {
		data3 = 0;
	}

	WREG32(mmUVD_SUVD_CGC_GATE, data1);
	WREG32(mmUVD_CGC_GATE, data3);
}