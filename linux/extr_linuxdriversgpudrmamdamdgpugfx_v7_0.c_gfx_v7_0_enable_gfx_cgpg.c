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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_GFX_PG ; 
 int /*<<< orphan*/  RLC_AUTO_PG_CTRL__AUTO_PG_EN_MASK ; 
 int /*<<< orphan*/  RLC_PG_CNTL__GFX_POWER_GATING_ENABLE_MASK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDB_RENDER_CONTROL ; 
 int /*<<< orphan*/  mmRLC_AUTO_PG_CTRL ; 
 int /*<<< orphan*/  mmRLC_PG_CNTL ; 

__attribute__((used)) static void gfx_v7_0_enable_gfx_cgpg(struct amdgpu_device *adev,
				     bool enable)
{
	u32 data, orig;

	if (enable && (adev->pg_flags & AMD_PG_SUPPORT_GFX_PG)) {
		orig = data = RREG32(mmRLC_PG_CNTL);
		data |= RLC_PG_CNTL__GFX_POWER_GATING_ENABLE_MASK;
		if (orig != data)
			WREG32(mmRLC_PG_CNTL, data);

		orig = data = RREG32(mmRLC_AUTO_PG_CTRL);
		data |= RLC_AUTO_PG_CTRL__AUTO_PG_EN_MASK;
		if (orig != data)
			WREG32(mmRLC_AUTO_PG_CTRL, data);
	} else {
		orig = data = RREG32(mmRLC_PG_CNTL);
		data &= ~RLC_PG_CNTL__GFX_POWER_GATING_ENABLE_MASK;
		if (orig != data)
			WREG32(mmRLC_PG_CNTL, data);

		orig = data = RREG32(mmRLC_AUTO_PG_CTRL);
		data &= ~RLC_AUTO_PG_CTRL__AUTO_PG_EN_MASK;
		if (orig != data)
			WREG32(mmRLC_AUTO_PG_CTRL, data);

		data = RREG32(mmDB_RENDER_CONTROL);
	}
}