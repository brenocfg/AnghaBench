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
struct intel_crtc_state {int /*<<< orphan*/  gamma_mode; } ;
struct drm_i915_private {int dummy; } ;
struct drm_crtc_state {TYPE_3__* crtc; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_5__ {int /*<<< orphan*/  degamma_lut_size; } ;
struct TYPE_8__ {TYPE_1__ color; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_MODE (int) ; 
 int /*<<< orphan*/  GAMMA_MODE_MODE_SPLIT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* INTEL_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREC_PAL_INDEX (int) ; 
 int /*<<< orphan*/  bdw_load_degamma_lut (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  bdw_load_gamma_lut (struct drm_crtc_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ crtc_state_is_legacy_gamma (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  haswell_load_luts (struct drm_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_intel_crtc (TYPE_3__*) ; 
 struct intel_crtc_state* to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void broadwell_load_luts(struct drm_crtc_state *state)
{
	struct drm_i915_private *dev_priv = to_i915(state->crtc->dev);
	struct intel_crtc_state *intel_state = to_intel_crtc_state(state);
	enum pipe pipe = to_intel_crtc(state->crtc)->pipe;

	if (crtc_state_is_legacy_gamma(state)) {
		haswell_load_luts(state);
		return;
	}

	bdw_load_degamma_lut(state);
	bdw_load_gamma_lut(state,
			   INTEL_INFO(dev_priv)->color.degamma_lut_size);

	intel_state->gamma_mode = GAMMA_MODE_MODE_SPLIT;
	I915_WRITE(GAMMA_MODE(pipe), GAMMA_MODE_MODE_SPLIT);
	POSTING_READ(GAMMA_MODE(pipe));

	/*
	 * Reset the index, otherwise it prevents the legacy palette to be
	 * written properly.
	 */
	I915_WRITE(PREC_PAL_INDEX(pipe), 0);
}