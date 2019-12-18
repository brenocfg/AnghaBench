#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int crtc_clock; } ;
struct TYPE_11__ {int /*<<< orphan*/  state; TYPE_2__ adjusted_mode; int /*<<< orphan*/  enable; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_5__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_9__ {int cdclk; } ;
struct TYPE_10__ {TYPE_3__ logical; } ;
struct TYPE_12__ {TYPE_4__ cdclk; } ;

/* Variables and functions */
 int DRM_PLANE_HELPER_NO_SCALING ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ is_planar_yuv_format (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_6__* to_intel_atomic_state (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

int
skl_max_scale(const struct intel_crtc_state *crtc_state,
	      u32 pixel_format)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	int max_scale, mult;
	int crtc_clock, max_dotclk, tmpclk1, tmpclk2;

	if (!crtc_state->base.enable)
		return DRM_PLANE_HELPER_NO_SCALING;

	crtc_clock = crtc_state->base.adjusted_mode.crtc_clock;
	max_dotclk = to_intel_atomic_state(crtc_state->base.state)->cdclk.logical.cdclk;

	if (IS_GEMINILAKE(dev_priv) || INTEL_GEN(dev_priv) >= 10)
		max_dotclk *= 2;

	if (WARN_ON_ONCE(!crtc_clock || max_dotclk < crtc_clock))
		return DRM_PLANE_HELPER_NO_SCALING;

	/*
	 * skl max scale is lower of:
	 *    close to 3 but not 3, -1 is for that purpose
	 *            or
	 *    cdclk/crtc_clock
	 */
	mult = is_planar_yuv_format(pixel_format) ? 2 : 3;
	tmpclk1 = (1 << 16) * mult - 1;
	tmpclk2 = (1 << 8) * ((max_dotclk << 8) / crtc_clock);
	max_scale = min(tmpclk1, tmpclk2);

	return max_scale;
}