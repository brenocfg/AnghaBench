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
struct radeon_device {int cg_flags; } ;

/* Variables and functions */
 int RADEON_CG_SUPPORT_VCE_MGCG ; 
 int /*<<< orphan*/  vce_v2_0_disable_cg (struct radeon_device*) ; 
 int /*<<< orphan*/  vce_v2_0_set_dyn_cg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  vce_v2_0_set_sw_cg (struct radeon_device*,int) ; 

void vce_v2_0_enable_mgcg(struct radeon_device *rdev, bool enable)
{
	bool sw_cg = false;

	if (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_VCE_MGCG)) {
		if (sw_cg)
			vce_v2_0_set_sw_cg(rdev, true);
		else
			vce_v2_0_set_dyn_cg(rdev, true);
	} else {
		vce_v2_0_disable_cg(rdev);

		if (sw_cg)
			vce_v2_0_set_sw_cg(rdev, false);
		else
			vce_v2_0_set_dyn_cg(rdev, false);
	}
}