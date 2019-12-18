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
 int AMD_PG_SUPPORT_GFX_PIPELINE ; 
 int /*<<< orphan*/  cz_enable_gfx_cg_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cz_enable_gfx_pipeline_power_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static void cz_update_gfx_cg_power_gating(struct amdgpu_device *adev,
					  bool enable)
{
	if ((adev->pg_flags & AMD_PG_SUPPORT_GFX_PG) && enable) {
		cz_enable_gfx_cg_power_gating(adev, true);
		if (adev->pg_flags & AMD_PG_SUPPORT_GFX_PIPELINE)
			cz_enable_gfx_pipeline_power_gating(adev, true);
	} else {
		cz_enable_gfx_cg_power_gating(adev, false);
		cz_enable_gfx_pipeline_power_gating(adev, false);
	}
}