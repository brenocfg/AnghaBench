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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int crtc_w; int rotation; TYPE_1__* plane; } ;
struct intel_plane_state {TYPE_3__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_MODE_ROTATE_180 ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MCURSOR_GAMMA_ENABLE ; 
 int /*<<< orphan*/  MCURSOR_MODE_128_ARGB_AX ; 
 int /*<<< orphan*/  MCURSOR_MODE_256_ARGB_AX ; 
 int /*<<< orphan*/  MCURSOR_MODE_64_ARGB_AX ; 
 int /*<<< orphan*/  MCURSOR_PIPE_CSC_ENABLE ; 
 int /*<<< orphan*/  MCURSOR_PIPE_SELECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCURSOR_ROTATE_180 ; 
 int /*<<< orphan*/  MCURSOR_TRICKLE_FEED_DISABLE ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i9xx_cursor_ctl(const struct intel_crtc_state *crtc_state,
			   const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv =
		to_i915(plane_state->base.plane->dev);
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	u32 cntl = 0;

	if (IS_GEN6(dev_priv) || IS_IVYBRIDGE(dev_priv))
		cntl |= MCURSOR_TRICKLE_FEED_DISABLE;

	if (INTEL_GEN(dev_priv) <= 10) {
		cntl |= MCURSOR_GAMMA_ENABLE;

		if (HAS_DDI(dev_priv))
			cntl |= MCURSOR_PIPE_CSC_ENABLE;
	}

	if (INTEL_GEN(dev_priv) < 5 && !IS_G4X(dev_priv))
		cntl |= MCURSOR_PIPE_SELECT(crtc->pipe);

	switch (plane_state->base.crtc_w) {
	case 64:
		cntl |= MCURSOR_MODE_64_ARGB_AX;
		break;
	case 128:
		cntl |= MCURSOR_MODE_128_ARGB_AX;
		break;
	case 256:
		cntl |= MCURSOR_MODE_256_ARGB_AX;
		break;
	default:
		MISSING_CASE(plane_state->base.crtc_w);
		return 0;
	}

	if (plane_state->base.rotation & DRM_MODE_ROTATE_180)
		cntl |= MCURSOR_ROTATE_180;

	return cntl;
}