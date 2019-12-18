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
 int AMD_PG_SUPPORT_GFX_DMG ; 
 int /*<<< orphan*/  RLC_PG_CNTL__DYN_PER_CU_PG_ENABLE_MASK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmRLC_PG_CNTL ; 

__attribute__((used)) static void gfx_v6_0_enable_gfx_dynamic_mgpg(struct amdgpu_device *adev,
					     bool enable)
{
	u32 data, orig;

	orig = data = RREG32(mmRLC_PG_CNTL);
	if (enable && (adev->pg_flags & AMD_PG_SUPPORT_GFX_DMG))
		data |= RLC_PG_CNTL__DYN_PER_CU_PG_ENABLE_MASK;
	else
		data &= ~RLC_PG_CNTL__DYN_PER_CU_PG_ENABLE_MASK;
	if (orig != data)
		WREG32(mmRLC_PG_CNTL, data);
}