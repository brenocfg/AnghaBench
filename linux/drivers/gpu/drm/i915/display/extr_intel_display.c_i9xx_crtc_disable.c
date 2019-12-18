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
struct TYPE_3__ {struct drm_crtc* crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_crtc {int pipe; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  initial_watermarks; } ;
struct drm_i915_private {TYPE_2__ display; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_DSI ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  assert_vblank_disabled (struct drm_crtc*) ; 
 int /*<<< orphan*/  chv_disable_pll (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  i830_enable_pipe (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  i9xx_disable_pll (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  i9xx_pfit_disable (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_disable_pipe (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_encoders_disable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_post_disable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_post_pll_disable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  intel_update_watermarks (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  vlv_disable_pll (struct drm_i915_private*,int) ; 

__attribute__((used)) static void i9xx_crtc_disable(struct intel_crtc_state *old_crtc_state,
			      struct intel_atomic_state *state)
{
	struct drm_crtc *crtc = old_crtc_state->base.crtc;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;

	/*
	 * On gen2 planes are double buffered but the pipe isn't, so we must
	 * wait for planes to fully turn off before disabling the pipe.
	 */
	if (IS_GEN(dev_priv, 2))
		intel_wait_for_vblank(dev_priv, pipe);

	intel_encoders_disable(intel_crtc, old_crtc_state, state);

	drm_crtc_vblank_off(crtc);
	assert_vblank_disabled(crtc);

	intel_disable_pipe(old_crtc_state);

	i9xx_pfit_disable(old_crtc_state);

	intel_encoders_post_disable(intel_crtc, old_crtc_state, state);

	if (!intel_crtc_has_type(old_crtc_state, INTEL_OUTPUT_DSI)) {
		if (IS_CHERRYVIEW(dev_priv))
			chv_disable_pll(dev_priv, pipe);
		else if (IS_VALLEYVIEW(dev_priv))
			vlv_disable_pll(dev_priv, pipe);
		else
			i9xx_disable_pll(old_crtc_state);
	}

	intel_encoders_post_pll_disable(intel_crtc, old_crtc_state, state);

	if (!IS_GEN(dev_priv, 2))
		intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, false);

	if (!dev_priv->display.initial_watermarks)
		intel_update_watermarks(intel_crtc);

	/* clock the pipe down to 640x480@60 to potentially save power */
	if (IS_I830(dev_priv))
		i830_enable_pipe(dev_priv, pipe);
}