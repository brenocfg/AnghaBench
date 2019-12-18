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
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_CP ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmRLC_PG_CNTL ; 

__attribute__((used)) static void gfx_v7_0_enable_cp_pg(struct amdgpu_device *adev, bool enable)
{
	u32 data, orig;

	orig = data = RREG32(mmRLC_PG_CNTL);
	if (enable && (adev->pg_flags & AMD_PG_SUPPORT_CP))
		data &= ~0x8000;
	else
		data |= 0x8000;
	if (orig != data)
		WREG32(mmRLC_PG_CNTL, data);
}