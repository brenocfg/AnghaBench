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
struct intel_crtc {int pipe; int active; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* initial_watermarks ) (struct intel_atomic_state*,struct intel_crtc_state*) ;} ;
struct drm_i915_private {TYPE_2__ display; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHV_BLEND (int) ; 
 int /*<<< orphan*/  CHV_BLEND_LEGACY ; 
 int /*<<< orphan*/  CHV_CANVAS (int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  M1_N1 ; 
 int PIPE_B ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_vblank_disabled (struct drm_crtc*) ; 
 int /*<<< orphan*/  chv_enable_pll (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  chv_prepare_pll (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  i9xx_pfit_enable (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  i9xx_set_pipeconf (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_color_commit (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_color_load_luts (struct intel_crtc_state*) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_crtc_vblank_on (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_disable_primary_plane (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_dp_set_m_n (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_enable_pipe (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_encoders_enable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_pre_enable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_pre_pll_enable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  intel_set_pipe_src_size (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_set_pipe_timings (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  vlv_enable_pll (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  vlv_prepare_pll (struct intel_crtc*,struct intel_crtc_state*) ; 

__attribute__((used)) static void valleyview_crtc_enable(struct intel_crtc_state *pipe_config,
				   struct intel_atomic_state *state)
{
	struct drm_crtc *crtc = pipe_config->base.crtc;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;

	if (WARN_ON(intel_crtc->active))
		return;

	if (intel_crtc_has_dp_encoder(pipe_config))
		intel_dp_set_m_n(pipe_config, M1_N1);

	intel_set_pipe_timings(pipe_config);
	intel_set_pipe_src_size(pipe_config);

	if (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B) {
		I915_WRITE(CHV_BLEND(pipe), CHV_BLEND_LEGACY);
		I915_WRITE(CHV_CANVAS(pipe), 0);
	}

	i9xx_set_pipeconf(pipe_config);

	intel_crtc->active = true;

	intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, true);

	intel_encoders_pre_pll_enable(intel_crtc, pipe_config, state);

	if (IS_CHERRYVIEW(dev_priv)) {
		chv_prepare_pll(intel_crtc, pipe_config);
		chv_enable_pll(intel_crtc, pipe_config);
	} else {
		vlv_prepare_pll(intel_crtc, pipe_config);
		vlv_enable_pll(intel_crtc, pipe_config);
	}

	intel_encoders_pre_enable(intel_crtc, pipe_config, state);

	i9xx_pfit_enable(pipe_config);

	intel_color_load_luts(pipe_config);
	intel_color_commit(pipe_config);
	/* update DSPCNTR to configure gamma for pipe bottom color */
	intel_disable_primary_plane(pipe_config);

	dev_priv->display.initial_watermarks(state, pipe_config);
	intel_enable_pipe(pipe_config);

	assert_vblank_disabled(crtc);
	intel_crtc_vblank_on(pipe_config);

	intel_encoders_enable(intel_crtc, pipe_config, state);
}