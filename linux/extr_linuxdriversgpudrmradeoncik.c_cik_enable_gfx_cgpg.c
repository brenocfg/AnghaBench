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
struct radeon_device {int pg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_PG_EN ; 
 int /*<<< orphan*/  DB_RENDER_CONTROL ; 
 int /*<<< orphan*/  GFX_PG_ENABLE ; 
 int RADEON_PG_SUPPORT_GFX_PG ; 
 int /*<<< orphan*/  RLC_AUTO_PG_CTRL ; 
 int /*<<< orphan*/  RLC_PG_CNTL ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cik_enable_gfx_cgpg(struct radeon_device *rdev,
				bool enable)
{
	u32 data, orig;

	if (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG)) {
		orig = data = RREG32(RLC_PG_CNTL);
		data |= GFX_PG_ENABLE;
		if (orig != data)
			WREG32(RLC_PG_CNTL, data);

		orig = data = RREG32(RLC_AUTO_PG_CTRL);
		data |= AUTO_PG_EN;
		if (orig != data)
			WREG32(RLC_AUTO_PG_CTRL, data);
	} else {
		orig = data = RREG32(RLC_PG_CNTL);
		data &= ~GFX_PG_ENABLE;
		if (orig != data)
			WREG32(RLC_PG_CNTL, data);

		orig = data = RREG32(RLC_AUTO_PG_CTRL);
		data &= ~AUTO_PG_EN;
		if (orig != data)
			WREG32(RLC_AUTO_PG_CTRL, data);

		data = RREG32(DB_RENDER_CONTROL);
	}
}