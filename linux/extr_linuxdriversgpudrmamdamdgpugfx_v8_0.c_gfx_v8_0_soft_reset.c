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
typedef  int u32 ;
struct TYPE_2__ {int grbm_soft_reset; int srbm_soft_reset; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_CLEAR ; 
 int /*<<< orphan*/  GFX_STALL ; 
 int /*<<< orphan*/  GMCON_DEBUG ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmGMCON_DEBUG ; 
 int /*<<< orphan*/  mmGRBM_SOFT_RESET ; 
 int /*<<< orphan*/  mmSRBM_SOFT_RESET ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gfx_v8_0_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 tmp;

	if ((!adev->gfx.grbm_soft_reset) &&
	    (!adev->gfx.srbm_soft_reset))
		return 0;

	grbm_soft_reset = adev->gfx.grbm_soft_reset;
	srbm_soft_reset = adev->gfx.srbm_soft_reset;

	if (grbm_soft_reset || srbm_soft_reset) {
		tmp = RREG32(mmGMCON_DEBUG);
		tmp = REG_SET_FIELD(tmp, GMCON_DEBUG, GFX_STALL, 1);
		tmp = REG_SET_FIELD(tmp, GMCON_DEBUG, GFX_CLEAR, 1);
		WREG32(mmGMCON_DEBUG, tmp);
		udelay(50);
	}

	if (grbm_soft_reset) {
		tmp = RREG32(mmGRBM_SOFT_RESET);
		tmp |= grbm_soft_reset;
		dev_info(adev->dev, "GRBM_SOFT_RESET=0x%08X\n", tmp);
		WREG32(mmGRBM_SOFT_RESET, tmp);
		tmp = RREG32(mmGRBM_SOFT_RESET);

		udelay(50);

		tmp &= ~grbm_soft_reset;
		WREG32(mmGRBM_SOFT_RESET, tmp);
		tmp = RREG32(mmGRBM_SOFT_RESET);
	}

	if (srbm_soft_reset) {
		tmp = RREG32(mmSRBM_SOFT_RESET);
		tmp |= srbm_soft_reset;
		dev_info(adev->dev, "SRBM_SOFT_RESET=0x%08X\n", tmp);
		WREG32(mmSRBM_SOFT_RESET, tmp);
		tmp = RREG32(mmSRBM_SOFT_RESET);

		udelay(50);

		tmp &= ~srbm_soft_reset;
		WREG32(mmSRBM_SOFT_RESET, tmp);
		tmp = RREG32(mmSRBM_SOFT_RESET);
	}

	if (grbm_soft_reset || srbm_soft_reset) {
		tmp = RREG32(mmGMCON_DEBUG);
		tmp = REG_SET_FIELD(tmp, GMCON_DEBUG, GFX_STALL, 0);
		tmp = REG_SET_FIELD(tmp, GMCON_DEBUG, GFX_CLEAR, 0);
		WREG32(mmGMCON_DEBUG, tmp);
	}

	/* Wait a little for things to settle down */
	udelay(50);

	return 0;
}