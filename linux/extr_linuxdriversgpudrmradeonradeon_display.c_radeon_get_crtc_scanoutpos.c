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
struct TYPE_4__ {TYPE_1__** crtcs; } ;
struct radeon_device {TYPE_2__ mode_info; } ;
struct drm_display_mode {int crtc_vdisplay; int crtc_vtotal; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {scalar_t__ lb_vblank_lead_lines; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ AVIVO_D1CRTC_STATUS_POSITION ; 
 scalar_t__ AVIVO_D1CRTC_V_BLANK_START_END ; 
 scalar_t__ AVIVO_D2CRTC_STATUS_POSITION ; 
 scalar_t__ AVIVO_D2CRTC_V_BLANK_START_END ; 
 int DRM_SCANOUTPOS_ACCURATE ; 
 int DRM_SCANOUTPOS_IN_VBLANK ; 
 int DRM_SCANOUTPOS_VALID ; 
 scalar_t__ EVERGREEN_CRTC0_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC1_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC2_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC3_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC4_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC5_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC_STATUS_POSITION ; 
 scalar_t__ EVERGREEN_CRTC_V_BLANK_START_END ; 
 unsigned int GET_DISTANCE_TO_VBLANKSTART ; 
 scalar_t__ RADEON_CRTC2_STATUS ; 
 scalar_t__ RADEON_CRTC2_VLINE_CRNT_VLINE ; 
 scalar_t__ RADEON_CRTC2_V_TOTAL_DISP ; 
 scalar_t__ RADEON_CRTC_STATUS ; 
 scalar_t__ RADEON_CRTC_VLINE_CRNT_VLINE ; 
 int RADEON_CRTC_V_DISP ; 
 int RADEON_CRTC_V_DISP_SHIFT ; 
 int RADEON_CRTC_V_TOTAL ; 
 scalar_t__ RADEON_CRTC_V_TOTAL_DISP ; 
 int RREG32 (scalar_t__) ; 
 unsigned int USE_REAL_VBLANKSTART ; 
 int /*<<< orphan*/  ktime_get () ; 

int radeon_get_crtc_scanoutpos(struct drm_device *dev, unsigned int pipe,
			       unsigned int flags, int *vpos, int *hpos,
			       ktime_t *stime, ktime_t *etime,
			       const struct drm_display_mode *mode)
{
	u32 stat_crtc = 0, vbl = 0, position = 0;
	int vbl_start, vbl_end, vtotal, ret = 0;
	bool in_vbl = true;

	struct radeon_device *rdev = dev->dev_private;

	/* preempt_disable_rt() should go right here in PREEMPT_RT patchset. */

	/* Get optional system timestamp before query. */
	if (stime)
		*stime = ktime_get();

	if (ASIC_IS_DCE4(rdev)) {
		if (pipe == 0) {
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC0_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC0_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		}
		if (pipe == 1) {
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC1_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC1_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		}
		if (pipe == 2) {
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC2_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC2_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		}
		if (pipe == 3) {
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC3_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC3_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		}
		if (pipe == 4) {
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC4_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC4_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		}
		if (pipe == 5) {
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC5_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC5_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		}
	} else if (ASIC_IS_AVIVO(rdev)) {
		if (pipe == 0) {
			vbl = RREG32(AVIVO_D1CRTC_V_BLANK_START_END);
			position = RREG32(AVIVO_D1CRTC_STATUS_POSITION);
			ret |= DRM_SCANOUTPOS_VALID;
		}
		if (pipe == 1) {
			vbl = RREG32(AVIVO_D2CRTC_V_BLANK_START_END);
			position = RREG32(AVIVO_D2CRTC_STATUS_POSITION);
			ret |= DRM_SCANOUTPOS_VALID;
		}
	} else {
		/* Pre-AVIVO: Different encoding of scanout pos and vblank interval. */
		if (pipe == 0) {
			/* Assume vbl_end == 0, get vbl_start from
			 * upper 16 bits.
			 */
			vbl = (RREG32(RADEON_CRTC_V_TOTAL_DISP) &
				RADEON_CRTC_V_DISP) >> RADEON_CRTC_V_DISP_SHIFT;
			/* Only retrieve vpos from upper 16 bits, set hpos == 0. */
			position = (RREG32(RADEON_CRTC_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
			stat_crtc = RREG32(RADEON_CRTC_STATUS);
			if (!(stat_crtc & 1))
				in_vbl = false;

			ret |= DRM_SCANOUTPOS_VALID;
		}
		if (pipe == 1) {
			vbl = (RREG32(RADEON_CRTC2_V_TOTAL_DISP) &
				RADEON_CRTC_V_DISP) >> RADEON_CRTC_V_DISP_SHIFT;
			position = (RREG32(RADEON_CRTC2_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
			stat_crtc = RREG32(RADEON_CRTC2_STATUS);
			if (!(stat_crtc & 1))
				in_vbl = false;

			ret |= DRM_SCANOUTPOS_VALID;
		}
	}

	/* Get optional system timestamp after query. */
	if (etime)
		*etime = ktime_get();

	/* preempt_enable_rt() should go right here in PREEMPT_RT patchset. */

	/* Decode into vertical and horizontal scanout position. */
	*vpos = position & 0x1fff;
	*hpos = (position >> 16) & 0x1fff;

	/* Valid vblank area boundaries from gpu retrieved? */
	if (vbl > 0) {
		/* Yes: Decode. */
		ret |= DRM_SCANOUTPOS_ACCURATE;
		vbl_start = vbl & 0x1fff;
		vbl_end = (vbl >> 16) & 0x1fff;
	}
	else {
		/* No: Fake something reasonable which gives at least ok results. */
		vbl_start = mode->crtc_vdisplay;
		vbl_end = 0;
	}

	/* Called from driver internal vblank counter query code? */
	if (flags & GET_DISTANCE_TO_VBLANKSTART) {
	    /* Caller wants distance from real vbl_start in *hpos */
	    *hpos = *vpos - vbl_start;
	}

	/* Fudge vblank to start a few scanlines earlier to handle the
	 * problem that vblank irqs fire a few scanlines before start
	 * of vblank. Some driver internal callers need the true vblank
	 * start to be used and signal this via the USE_REAL_VBLANKSTART flag.
	 *
	 * The cause of the "early" vblank irq is that the irq is triggered
	 * by the line buffer logic when the line buffer read position enters
	 * the vblank, whereas our crtc scanout position naturally lags the
	 * line buffer read position.
	 */
	if (!(flags & USE_REAL_VBLANKSTART))
		vbl_start -= rdev->mode_info.crtcs[pipe]->lb_vblank_lead_lines;

	/* Test scanout position against vblank region. */
	if ((*vpos < vbl_start) && (*vpos >= vbl_end))
		in_vbl = false;

	/* In vblank? */
	if (in_vbl)
	    ret |= DRM_SCANOUTPOS_IN_VBLANK;

	/* Called from driver internal vblank counter query code? */
	if (flags & GET_DISTANCE_TO_VBLANKSTART) {
		/* Caller wants distance from fudged earlier vbl_start */
		*vpos -= vbl_start;
		return ret;
	}

	/* Check if inside vblank area and apply corrective offsets:
	 * vpos will then be >=0 in video scanout area, but negative
	 * within vblank area, counting down the number of lines until
	 * start of scanout.
	 */

	/* Inside "upper part" of vblank area? Apply corrective offset if so: */
	if (in_vbl && (*vpos >= vbl_start)) {
		vtotal = mode->crtc_vtotal;
		*vpos = *vpos - vtotal;
	}

	/* Correct for shifted end of vbl at vbl_end. */
	*vpos = *vpos - vbl_end;

	return ret;
}