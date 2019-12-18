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
struct radeon_device {int pg_flags; } ;

/* Variables and functions */
 int AUTO_PG_EN ; 
 int /*<<< orphan*/  DB_RENDER_CONTROL ; 
 int GFX_PG_ENABLE ; 
 int RADEON_PG_SUPPORT_GFX_PG ; 
 int /*<<< orphan*/  RLC_AUTO_PG_CTRL ; 
 int RLC_MSD (int) ; 
 int RLC_PDD (int) ; 
 int /*<<< orphan*/  RLC_PG_CNTL ; 
 int RLC_PUD (int) ; 
 int /*<<< orphan*/  RLC_TTOP_D ; 
 int RLC_TTPD (int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_enable_gfx_cgpg(struct radeon_device *rdev,
			       bool enable)
{
	u32 tmp;

	if (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG)) {
		tmp = RLC_PUD(0x10) | RLC_PDD(0x10) | RLC_TTPD(0x10) | RLC_MSD(0x10);
		WREG32(RLC_TTOP_D, tmp);

		tmp = RREG32(RLC_PG_CNTL);
		tmp |= GFX_PG_ENABLE;
		WREG32(RLC_PG_CNTL, tmp);

		tmp = RREG32(RLC_AUTO_PG_CTRL);
		tmp |= AUTO_PG_EN;
		WREG32(RLC_AUTO_PG_CTRL, tmp);
	} else {
		tmp = RREG32(RLC_AUTO_PG_CTRL);
		tmp &= ~AUTO_PG_EN;
		WREG32(RLC_AUTO_PG_CTRL, tmp);

		tmp = RREG32(DB_RENDER_CONTROL);
	}
}