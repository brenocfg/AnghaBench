#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct radeon_crtc** crtcs; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct radeon_crtc {scalar_t__ crtc_offset; } ;

/* Variables and functions */
 int AVIVO_D1GRPH_SURFACE_UPDATE_PENDING ; 
 scalar_t__ AVIVO_D1GRPH_UPDATE ; 
 int RREG32 (scalar_t__) ; 

bool rv770_page_flip_pending(struct radeon_device *rdev, int crtc_id)
{
	struct radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];

	/* Return current update_pending status: */
	return !!(RREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset) &
		AVIVO_D1GRPH_SURFACE_UPDATE_PENDING);
}