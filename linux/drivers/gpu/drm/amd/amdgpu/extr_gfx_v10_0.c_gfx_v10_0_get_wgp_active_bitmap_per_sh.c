#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int max_cu_per_sh; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int CC_GC_SHADER_ARRAY_CONFIG__INACTIVE_WGPS_MASK ; 
 int CC_GC_SHADER_ARRAY_CONFIG__INACTIVE_WGPS__SHIFT ; 
 int /*<<< orphan*/  GC ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_gfx_create_bitmask (int) ; 
 int /*<<< orphan*/  mmCC_GC_SHADER_ARRAY_CONFIG ; 
 int /*<<< orphan*/  mmGC_USER_SHADER_ARRAY_CONFIG ; 

__attribute__((used)) static u32 gfx_v10_0_get_wgp_active_bitmap_per_sh(struct amdgpu_device *adev)
{
	u32 data, wgp_bitmask;
	data = RREG32_SOC15(GC, 0, mmCC_GC_SHADER_ARRAY_CONFIG);
	data |= RREG32_SOC15(GC, 0, mmGC_USER_SHADER_ARRAY_CONFIG);

	data &= CC_GC_SHADER_ARRAY_CONFIG__INACTIVE_WGPS_MASK;
	data >>= CC_GC_SHADER_ARRAY_CONFIG__INACTIVE_WGPS__SHIFT;

	wgp_bitmask =
		amdgpu_gfx_create_bitmask(adev->gfx.config.max_cu_per_sh >> 1);

	return (~data) & wgp_bitmask;
}