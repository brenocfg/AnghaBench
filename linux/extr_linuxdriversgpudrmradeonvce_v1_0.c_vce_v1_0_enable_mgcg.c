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
struct radeon_device {int cg_flags; } ;

/* Variables and functions */
 int CGC_DYN_CLOCK_MODE ; 
 int RADEON_CG_SUPPORT_VCE_MGCG ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCE_CLOCK_GATING_A ; 
 int /*<<< orphan*/  VCE_UENC_CLOCK_GATING ; 
 int /*<<< orphan*/  VCE_UENC_REG_CLOCK_GATING ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void vce_v1_0_enable_mgcg(struct radeon_device *rdev, bool enable)
{
	u32 tmp;

	if (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_VCE_MGCG)) {
		tmp = RREG32(VCE_CLOCK_GATING_A);
		tmp |= CGC_DYN_CLOCK_MODE;
		WREG32(VCE_CLOCK_GATING_A, tmp);

		tmp = RREG32(VCE_UENC_CLOCK_GATING);
		tmp &= ~0x1ff000;
		tmp |= 0xff800000;
		WREG32(VCE_UENC_CLOCK_GATING, tmp);

		tmp = RREG32(VCE_UENC_REG_CLOCK_GATING);
		tmp &= ~0x3ff;
		WREG32(VCE_UENC_REG_CLOCK_GATING, tmp);
	} else {
		tmp = RREG32(VCE_CLOCK_GATING_A);
		tmp &= ~CGC_DYN_CLOCK_MODE;
		WREG32(VCE_CLOCK_GATING_A, tmp);

		tmp = RREG32(VCE_UENC_CLOCK_GATING);
		tmp |= 0x1ff000;
		tmp &= ~0xff800000;
		WREG32(VCE_UENC_CLOCK_GATING, tmp);

		tmp = RREG32(VCE_UENC_REG_CLOCK_GATING);
		tmp |= 0x3ff;
		WREG32(VCE_UENC_REG_CLOCK_GATING, tmp);
	}
}