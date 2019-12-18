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
struct radeon_device {int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_RLC_REQ_AND_RSP ; 
 int CG_RLC_RSP_TYPE_MASK ; 
 int CG_RLC_RSP_TYPE_SHIFT ; 
 int /*<<< orphan*/  DYN_GFX_CLK_OFF_EN ; 
 int /*<<< orphan*/  GRBM_PWR_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void r600_gfx_clockgating_enable(struct radeon_device *rdev, bool enable)
{
	int i;

	if (enable) {
		WREG32_P(SCLK_PWRMGT_CNTL, DYN_GFX_CLK_OFF_EN, ~DYN_GFX_CLK_OFF_EN);
	} else {
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_GFX_CLK_OFF_EN);

		WREG32(CG_RLC_REQ_AND_RSP, 0x2);

		for (i = 0; i < rdev->usec_timeout; i++) {
			if (((RREG32(CG_RLC_REQ_AND_RSP) & CG_RLC_RSP_TYPE_MASK) >> CG_RLC_RSP_TYPE_SHIFT) == 1)
				break;
			udelay(1);
		}

		WREG32(CG_RLC_REQ_AND_RSP, 0x0);

		WREG32(GRBM_PWR_CNTL, 0x1);
		RREG32(GRBM_PWR_CNTL);
	}
}