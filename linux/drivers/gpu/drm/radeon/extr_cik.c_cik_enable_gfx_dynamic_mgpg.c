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
 int /*<<< orphan*/  DYN_PER_CU_PG_ENABLE ; 
 int RADEON_PG_SUPPORT_GFX_DMG ; 
 int /*<<< orphan*/  RLC_PG_CNTL ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cik_enable_gfx_dynamic_mgpg(struct radeon_device *rdev,
					bool enable)
{
	u32 data, orig;

	orig = data = RREG32(RLC_PG_CNTL);
	if (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_DMG))
		data |= DYN_PER_CU_PG_ENABLE;
	else
		data &= ~DYN_PER_CU_PG_ENABLE;
	if (orig != data)
		WREG32(RLC_PG_CNTL, data);
}