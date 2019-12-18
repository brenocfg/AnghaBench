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
struct rv6xx_pl {int mclk; } ;
struct rv6xx_ps {struct rv6xx_pl high; struct rv6xx_pl medium; struct rv6xx_pl low; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {struct radeon_ps* current_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int CURRENT_PROFILE_INDEX_MASK ; 
 int CURRENT_PROFILE_INDEX_SHIFT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 struct rv6xx_ps* rv6xx_get_ps (struct radeon_ps*) ; 

u32 rv6xx_dpm_get_current_mclk(struct radeon_device *rdev)
{
	struct radeon_ps *rps = rdev->pm.dpm.current_ps;
	struct rv6xx_ps *ps = rv6xx_get_ps(rps);
	struct rv6xx_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROFILE_INDEX) & CURRENT_PROFILE_INDEX_MASK) >>
		CURRENT_PROFILE_INDEX_SHIFT;

	if (current_index > 2) {
		return 0;
	} else {
		if (current_index == 0)
			pl = &ps->low;
		else if (current_index == 1)
			pl = &ps->medium;
		else /* current_index == 2 */
			pl = &ps->high;
		return pl->mclk;
	}
}