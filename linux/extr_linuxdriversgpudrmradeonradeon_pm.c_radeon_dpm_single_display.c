#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int new_active_crtc_count; } ;
struct TYPE_6__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_4__* asic; TYPE_2__ pm; } ;
struct TYPE_7__ {scalar_t__ vblank_too_short; } ;
struct TYPE_8__ {TYPE_3__ dpm; } ;

/* Variables and functions */
 int r600_dpm_get_vrefresh (struct radeon_device*) ; 
 scalar_t__ radeon_dpm_vblank_too_short (struct radeon_device*) ; 

__attribute__((used)) static bool radeon_dpm_single_display(struct radeon_device *rdev)
{
	bool single_display = (rdev->pm.dpm.new_active_crtc_count < 2) ?
		true : false;

	/* check if the vblank period is too short to adjust the mclk */
	if (single_display && rdev->asic->dpm.vblank_too_short) {
		if (radeon_dpm_vblank_too_short(rdev))
			single_display = false;
	}

	/* 120hz tends to be problematic even if they are under the
	 * vblank limit.
	 */
	if (single_display && (r600_dpm_get_vrefresh(rdev) >= 120))
		single_display = false;

	return single_display;
}