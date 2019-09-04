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
struct intel_crtc_state {int /*<<< orphan*/  gamma_mode; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc_state {struct drm_crtc* crtc; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_2__ {int pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_MODE (int) ; 
 int /*<<< orphan*/  GAMMA_MODE_MODE_10BIT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdw_load_gamma_lut (struct drm_crtc_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ crtc_state_is_legacy_gamma (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  glk_load_degamma_lut (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  haswell_load_luts (struct drm_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 TYPE_1__* to_intel_crtc (struct drm_crtc*) ; 
 struct intel_crtc_state* to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void glk_load_luts(struct drm_crtc_state *state)
{
	struct drm_crtc *crtc = state->crtc;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc_state *intel_state = to_intel_crtc_state(state);
	enum pipe pipe = to_intel_crtc(crtc)->pipe;

	glk_load_degamma_lut(state);

	if (crtc_state_is_legacy_gamma(state)) {
		haswell_load_luts(state);
		return;
	}

	bdw_load_gamma_lut(state, 0);

	intel_state->gamma_mode = GAMMA_MODE_MODE_10BIT;
	I915_WRITE(GAMMA_MODE(pipe), GAMMA_MODE_MODE_10BIT);
	POSTING_READ(GAMMA_MODE(pipe));
}