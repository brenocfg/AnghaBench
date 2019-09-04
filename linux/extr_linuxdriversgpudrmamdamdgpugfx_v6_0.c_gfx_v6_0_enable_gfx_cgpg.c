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
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_GFX_PG ; 
 int /*<<< orphan*/  AUTO_PG_EN ; 
 int /*<<< orphan*/  GFX_POWER_GATING_ENABLE ; 
 int /*<<< orphan*/  RLC_AUTO_PG_CTRL ; 
 int RLC_MSD (int) ; 
 int RLC_PDD (int) ; 
 int /*<<< orphan*/  RLC_PG_CNTL ; 
 int RLC_PUD (int) ; 
 int RLC_TTPD (int) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmDB_RENDER_CONTROL ; 
 int /*<<< orphan*/  mmRLC_TTOP_D ; 

__attribute__((used)) static void gfx_v6_0_enable_gfx_cgpg(struct amdgpu_device *adev,
				     bool enable)
{
	if (enable && (adev->pg_flags & AMD_PG_SUPPORT_GFX_PG)) {
		WREG32(mmRLC_TTOP_D, RLC_PUD(0x10) | RLC_PDD(0x10) | RLC_TTPD(0x10) | RLC_MSD(0x10));
		WREG32_FIELD(RLC_PG_CNTL, GFX_POWER_GATING_ENABLE, 1);
		WREG32_FIELD(RLC_AUTO_PG_CTRL, AUTO_PG_EN, 1);
	} else {
		WREG32_FIELD(RLC_AUTO_PG_CTRL, AUTO_PG_EN, 0);
		(void)RREG32(mmDB_RENDER_CONTROL);
	}
}