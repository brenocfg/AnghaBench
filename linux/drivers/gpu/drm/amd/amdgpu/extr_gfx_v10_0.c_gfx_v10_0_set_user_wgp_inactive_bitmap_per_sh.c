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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_WGPS_MASK ; 
 int GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_WGPS__SHIFT ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmGC_USER_SHADER_ARRAY_CONFIG ; 

__attribute__((used)) static void gfx_v10_0_set_user_wgp_inactive_bitmap_per_sh(struct amdgpu_device *adev,
							  u32 bitmap)
{
	u32 data;

	if (!bitmap)
		return;

	data = bitmap << GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_WGPS__SHIFT;
	data &= GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_WGPS_MASK;

	WREG32_SOC15(GC, 0, mmGC_USER_SHADER_ARRAY_CONFIG, data);
}