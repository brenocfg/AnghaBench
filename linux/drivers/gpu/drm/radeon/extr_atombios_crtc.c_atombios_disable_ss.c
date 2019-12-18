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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
#define  ATOM_DCPLL 131 
#define  ATOM_PPLL1 130 
#define  ATOM_PPLL2 129 
#define  ATOM_PPLL_INVALID 128 
 int /*<<< orphan*/  AVIVO_P1PLL_INT_SS_CNTL ; 
 int /*<<< orphan*/  AVIVO_P2PLL_INT_SS_CNTL ; 
 int /*<<< orphan*/  EVERGREEN_P1PLL_SS_CNTL ; 
 int /*<<< orphan*/  EVERGREEN_P2PLL_SS_CNTL ; 
 int EVERGREEN_PxPLL_SS_EN ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atombios_disable_ss(struct radeon_device *rdev, int pll_id)
{
	u32 ss_cntl;

	if (ASIC_IS_DCE4(rdev)) {
		switch (pll_id) {
		case ATOM_PPLL1:
			ss_cntl = RREG32(EVERGREEN_P1PLL_SS_CNTL);
			ss_cntl &= ~EVERGREEN_PxPLL_SS_EN;
			WREG32(EVERGREEN_P1PLL_SS_CNTL, ss_cntl);
			break;
		case ATOM_PPLL2:
			ss_cntl = RREG32(EVERGREEN_P2PLL_SS_CNTL);
			ss_cntl &= ~EVERGREEN_PxPLL_SS_EN;
			WREG32(EVERGREEN_P2PLL_SS_CNTL, ss_cntl);
			break;
		case ATOM_DCPLL:
		case ATOM_PPLL_INVALID:
			return;
		}
	} else if (ASIC_IS_AVIVO(rdev)) {
		switch (pll_id) {
		case ATOM_PPLL1:
			ss_cntl = RREG32(AVIVO_P1PLL_INT_SS_CNTL);
			ss_cntl &= ~1;
			WREG32(AVIVO_P1PLL_INT_SS_CNTL, ss_cntl);
			break;
		case ATOM_PPLL2:
			ss_cntl = RREG32(AVIVO_P2PLL_INT_SS_CNTL);
			ss_cntl &= ~1;
			WREG32(AVIVO_P2PLL_INT_SS_CNTL, ss_cntl);
			break;
		case ATOM_DCPLL:
		case ATOM_PPLL_INVALID:
			return;
		}
	}
}