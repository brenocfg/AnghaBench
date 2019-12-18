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
 int AMD_PG_SUPPORT_CP ; 
 int AMD_PG_SUPPORT_GDS ; 
 int AMD_PG_SUPPORT_GFX_DMG ; 
 int AMD_PG_SUPPORT_GFX_PG ; 
 int AMD_PG_SUPPORT_GFX_SMG ; 
 int AMD_PG_SUPPORT_RLC_SMU_HS ; 
 int /*<<< orphan*/  gfx_v7_0_enable_cp_pg (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_enable_gds_pg (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_enable_sclk_slowdown_on_pd (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_enable_sclk_slowdown_on_pu (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_init_ao_cu_mask (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_init_gfx_cgpg (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_update_gfx_pg (struct amdgpu_device*,int) ; 

__attribute__((used)) static void gfx_v7_0_init_pg(struct amdgpu_device *adev)
{
	if (adev->pg_flags & (AMD_PG_SUPPORT_GFX_PG |
			      AMD_PG_SUPPORT_GFX_SMG |
			      AMD_PG_SUPPORT_GFX_DMG |
			      AMD_PG_SUPPORT_CP |
			      AMD_PG_SUPPORT_GDS |
			      AMD_PG_SUPPORT_RLC_SMU_HS)) {
		gfx_v7_0_enable_sclk_slowdown_on_pu(adev, true);
		gfx_v7_0_enable_sclk_slowdown_on_pd(adev, true);
		if (adev->pg_flags & AMD_PG_SUPPORT_GFX_PG) {
			gfx_v7_0_init_gfx_cgpg(adev);
			gfx_v7_0_enable_cp_pg(adev, true);
			gfx_v7_0_enable_gds_pg(adev, true);
		}
		gfx_v7_0_init_ao_cu_mask(adev);
		gfx_v7_0_update_gfx_pg(adev, true);
	}
}