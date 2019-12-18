#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ rotation; scalar_t__ pixel_blend_mode; int adjusted_y; } ;
struct TYPE_12__ {int mode_flags; int hsw_bdw_pixel_rate; } ;
struct TYPE_11__ {TYPE_2__* format; int /*<<< orphan*/  stride; } ;
struct intel_fbc_state_cache {int flags; TYPE_8__ plane; TYPE_4__ crtc; TYPE_3__ fb; int /*<<< orphan*/  vma; } ;
struct TYPE_15__ {int size; } ;
struct intel_fbc {char* no_fbc_reason; int threshold; struct intel_fbc_state_cache state_cache; TYPE_7__ compressed_fb; scalar_t__ underrun_detected; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct TYPE_13__ {int cdclk; } ;
struct TYPE_14__ {TYPE_5__ hw; } ;
struct drm_i915_private {TYPE_6__ cdclk; struct intel_fbc fbc; } ;
struct TYPE_10__ {scalar_t__ has_alpha; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_BLEND_PIXEL_NONE ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ DRM_MODE_ROTATE_0 ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN_RANGE (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int PLANE_HAS_FENCE ; 
 int intel_fbc_calculate_cfb_size (struct drm_i915_private*,struct intel_fbc_state_cache*) ; 
 int /*<<< orphan*/  intel_fbc_hw_tracking_covers_screen (struct intel_crtc*) ; 
 int /*<<< orphan*/  pixel_format_is_valid (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stride_is_valid (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_fbc_can_activate(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_fbc *fbc = &dev_priv->fbc;
	struct intel_fbc_state_cache *cache = &fbc->state_cache;

	/* We don't need to use a state cache here since this information is
	 * global for all CRTC.
	 */
	if (fbc->underrun_detected) {
		fbc->no_fbc_reason = "underrun detected";
		return false;
	}

	if (!cache->vma) {
		fbc->no_fbc_reason = "primary plane not visible";
		return false;
	}

	if (cache->crtc.mode_flags & DRM_MODE_FLAG_INTERLACE) {
		fbc->no_fbc_reason = "incompatible mode";
		return false;
	}

	if (!intel_fbc_hw_tracking_covers_screen(crtc)) {
		fbc->no_fbc_reason = "mode too large for compression";
		return false;
	}

	/* The use of a CPU fence is mandatory in order to detect writes
	 * by the CPU to the scanout and trigger updates to the FBC.
	 *
	 * Note that is possible for a tiled surface to be unmappable (and
	 * so have no fence associated with it) due to aperture constaints
	 * at the time of pinning.
	 *
	 * FIXME with 90/270 degree rotation we should use the fence on
	 * the normal GTT view (the rotated view doesn't even have a
	 * fence). Would need changes to the FBC fence Y offset as well.
	 * For now this will effecively disable FBC with 90/270 degree
	 * rotation.
	 */
	if (!(cache->flags & PLANE_HAS_FENCE)) {
		fbc->no_fbc_reason = "framebuffer not tiled or fenced";
		return false;
	}
	if (INTEL_GEN(dev_priv) <= 4 && !IS_G4X(dev_priv) &&
	    cache->plane.rotation != DRM_MODE_ROTATE_0) {
		fbc->no_fbc_reason = "rotation unsupported";
		return false;
	}

	if (!stride_is_valid(dev_priv, cache->fb.stride)) {
		fbc->no_fbc_reason = "framebuffer stride not supported";
		return false;
	}

	if (!pixel_format_is_valid(dev_priv, cache->fb.format->format)) {
		fbc->no_fbc_reason = "pixel format is invalid";
		return false;
	}

	if (cache->plane.pixel_blend_mode != DRM_MODE_BLEND_PIXEL_NONE &&
	    cache->fb.format->has_alpha) {
		fbc->no_fbc_reason = "per-pixel alpha blending is incompatible with FBC";
		return false;
	}

	/* WaFbcExceedCdClockThreshold:hsw,bdw */
	if ((IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) &&
	    cache->crtc.hsw_bdw_pixel_rate >= dev_priv->cdclk.hw.cdclk * 95 / 100) {
		fbc->no_fbc_reason = "pixel rate is too big";
		return false;
	}

	/* It is possible for the required CFB size change without a
	 * crtc->disable + crtc->enable since it is possible to change the
	 * stride without triggering a full modeset. Since we try to
	 * over-allocate the CFB, there's a chance we may keep FBC enabled even
	 * if this happens, but if we exceed the current CFB size we'll have to
	 * disable FBC. Notice that it would be possible to disable FBC, wait
	 * for a frame, free the stolen node, then try to reenable FBC in case
	 * we didn't get any invalidate/deactivate calls, but this would require
	 * a lot of tracking just for a specific case. If we conclude it's an
	 * important case, we can implement it later. */
	if (intel_fbc_calculate_cfb_size(dev_priv, &fbc->state_cache) >
	    fbc->compressed_fb.size * fbc->threshold) {
		fbc->no_fbc_reason = "CFB requirements changed";
		return false;
	}

	/*
	 * Work around a problem on GEN9+ HW, where enabling FBC on a plane
	 * having a Y offset that isn't divisible by 4 causes FIFO underrun
	 * and screen flicker.
	 */
	if (IS_GEN_RANGE(dev_priv, 9, 10) &&
	    (fbc->state_cache.plane.adjusted_y & 3)) {
		fbc->no_fbc_reason = "plane Y offset is misaligned";
		return false;
	}

	return true;
}