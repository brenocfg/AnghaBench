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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfx_v8_0_update_coarse_grain_clock_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v8_0_update_medium_grain_clock_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static int gfx_v8_0_update_gfx_clock_gating(struct amdgpu_device *adev,
					    bool enable)
{
	if (enable) {
		/* CGCG/CGLS should be enabled after MGCG/MGLS/TS(CG/LS)
		 * ===  MGCG + MGLS + TS(CG/LS) ===
		 */
		gfx_v8_0_update_medium_grain_clock_gating(adev, enable);
		gfx_v8_0_update_coarse_grain_clock_gating(adev, enable);
	} else {
		/* CGCG/CGLS should be disabled before MGCG/MGLS/TS(CG/LS)
		 * ===  CGCG + CGLS ===
		 */
		gfx_v8_0_update_coarse_grain_clock_gating(adev, enable);
		gfx_v8_0_update_medium_grain_clock_gating(adev, enable);
	}
	return 0;
}