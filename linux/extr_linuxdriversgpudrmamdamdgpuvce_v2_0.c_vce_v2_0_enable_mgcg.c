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
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_VCE_MGCG ; 
 int /*<<< orphan*/  vce_v2_0_disable_cg (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vce_v2_0_set_dyn_cg (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  vce_v2_0_set_sw_cg (struct amdgpu_device*,int) ; 

__attribute__((used)) static void vce_v2_0_enable_mgcg(struct amdgpu_device *adev, bool enable,
								bool sw_cg)
{
	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_VCE_MGCG)) {
		if (sw_cg)
			vce_v2_0_set_sw_cg(adev, true);
		else
			vce_v2_0_set_dyn_cg(adev, true);
	} else {
		vce_v2_0_disable_cg(adev);

		if (sw_cg)
			vce_v2_0_set_sw_cg(adev, false);
		else
			vce_v2_0_set_dyn_cg(adev, false);
	}
}