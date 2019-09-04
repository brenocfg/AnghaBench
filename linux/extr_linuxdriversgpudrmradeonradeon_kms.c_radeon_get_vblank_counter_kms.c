#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {TYPE_2__** crtcs; } ;
struct radeon_device {unsigned int num_crtc; TYPE_3__ mode_info; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwmode; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_VBL (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 int DRM_SCANOUTPOS_ACCURATE ; 
 int DRM_SCANOUTPOS_VALID ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  GET_DISTANCE_TO_VBLANKSTART ; 
 int radeon_get_crtc_scanoutpos (struct drm_device*,unsigned int,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ radeon_get_vblank_counter (struct radeon_device*,unsigned int) ; 

u32 radeon_get_vblank_counter_kms(struct drm_device *dev, unsigned int pipe)
{
	int vpos, hpos, stat;
	u32 count;
	struct radeon_device *rdev = dev->dev_private;

	if (pipe >= rdev->num_crtc) {
		DRM_ERROR("Invalid crtc %u\n", pipe);
		return -EINVAL;
	}

	/* The hw increments its frame counter at start of vsync, not at start
	 * of vblank, as is required by DRM core vblank counter handling.
	 * Cook the hw count here to make it appear to the caller as if it
	 * incremented at start of vblank. We measure distance to start of
	 * vblank in vpos. vpos therefore will be >= 0 between start of vblank
	 * and start of vsync, so vpos >= 0 means to bump the hw frame counter
	 * result by 1 to give the proper appearance to caller.
	 */
	if (rdev->mode_info.crtcs[pipe]) {
		/* Repeat readout if needed to provide stable result if
		 * we cross start of vsync during the queries.
		 */
		do {
			count = radeon_get_vblank_counter(rdev, pipe);
			/* Ask radeon_get_crtc_scanoutpos to return vpos as
			 * distance to start of vblank, instead of regular
			 * vertical scanout pos.
			 */
			stat = radeon_get_crtc_scanoutpos(
				dev, pipe, GET_DISTANCE_TO_VBLANKSTART,
				&vpos, &hpos, NULL, NULL,
				&rdev->mode_info.crtcs[pipe]->base.hwmode);
		} while (count != radeon_get_vblank_counter(rdev, pipe));

		if (((stat & (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_ACCURATE)) !=
		    (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_ACCURATE))) {
			DRM_DEBUG_VBL("Query failed! stat %d\n", stat);
		}
		else {
			DRM_DEBUG_VBL("crtc %u: dist from vblank start %d\n",
				      pipe, vpos);

			/* Bump counter if we are at >= leading edge of vblank,
			 * but before vsync where vpos would turn negative and
			 * the hw counter really increments.
			 */
			if (vpos >= 0)
				count++;
		}
	}
	else {
	    /* Fallback to use value as is. */
	    count = radeon_get_vblank_counter(rdev, pipe);
	    DRM_DEBUG_VBL("NULL mode info! Returned count may be wrong.\n");
	}

	return count;
}