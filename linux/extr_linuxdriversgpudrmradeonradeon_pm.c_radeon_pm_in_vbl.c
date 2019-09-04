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
struct TYPE_8__ {TYPE_3__** crtcs; } ;
struct TYPE_5__ {int active_crtcs; } ;
struct radeon_device {int num_crtc; TYPE_4__ mode_info; int /*<<< orphan*/  ddev; TYPE_1__ pm; } ;
struct TYPE_6__ {int /*<<< orphan*/  hwmode; } ;
struct TYPE_7__ {TYPE_2__ base; } ;

/* Variables and functions */
 int DRM_SCANOUTPOS_IN_VBLANK ; 
 int DRM_SCANOUTPOS_VALID ; 
 int /*<<< orphan*/  USE_REAL_VBLANKSTART ; 
 int radeon_get_crtc_scanoutpos (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool radeon_pm_in_vbl(struct radeon_device *rdev)
{
	int  crtc, vpos, hpos, vbl_status;
	bool in_vbl = true;

	/* Iterate over all active crtc's. All crtc's must be in vblank,
	 * otherwise return in_vbl == false.
	 */
	for (crtc = 0; (crtc < rdev->num_crtc) && in_vbl; crtc++) {
		if (rdev->pm.active_crtcs & (1 << crtc)) {
			vbl_status = radeon_get_crtc_scanoutpos(rdev->ddev,
								crtc,
								USE_REAL_VBLANKSTART,
								&vpos, &hpos, NULL, NULL,
								&rdev->mode_info.crtcs[crtc]->base.hwmode);
			if ((vbl_status & DRM_SCANOUTPOS_VALID) &&
			    !(vbl_status & DRM_SCANOUTPOS_IN_VBLANK))
				in_vbl = false;
		}
	}

	return in_vbl;
}