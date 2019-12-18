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
struct TYPE_5__ {scalar_t__ enabled; } ;
struct TYPE_4__ {struct drm_crtc* crtc; } ;
struct intel_crtc_state {int cpu_transcoder; int hsw_workaround_pipe; scalar_t__ has_pch_encoder; TYPE_2__ pch_pfit; int /*<<< orphan*/  fdi_m_n; scalar_t__ pixel_multiplier; scalar_t__ shared_dpll; TYPE_1__ base; } ;
struct intel_crtc {int pipe; int active; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* initial_watermarks ) (struct intel_atomic_state*,struct intel_crtc_state*) ;} ;
struct drm_i915_private {TYPE_3__ display; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,scalar_t__) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DP_MST ; 
 int INVALID_PIPE ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  M1_N1 ; 
 int /*<<< orphan*/  PIPE_MULT (int) ; 
 int TRANSCODER_EDP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_vblank_disabled (struct drm_crtc*) ; 
 int /*<<< orphan*/  bdw_set_pipemisc (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  glk_pipe_scaler_clock_gating_wa (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  haswell_set_pipeconf (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  icl_pipe_mbus_enable (struct intel_crtc*) ; 
 int /*<<< orphan*/  icl_set_pipe_chicken (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_color_commit (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_color_load_luts (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_cpu_transcoder_set_m_n (struct intel_crtc_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_crtc_vblank_on (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_ddi_enable_transcoder_func (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_ddi_set_pipe_settings (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_ddi_set_vc_payload_alloc (struct intel_crtc_state*,int) ; 
 int /*<<< orphan*/  intel_disable_primary_plane (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_dp_set_m_n (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_enable_pipe (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_enable_shared_dpll (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_encoders_enable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_pre_enable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_pre_pll_enable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_set_pipe_src_size (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_set_pipe_timings (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  ironlake_pfit_enable (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  lpt_pch_enable (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  skylake_pfit_enable (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  transcoder_is_dsi (int) ; 

__attribute__((used)) static void haswell_crtc_enable(struct intel_crtc_state *pipe_config,
				struct intel_atomic_state *state)
{
	struct drm_crtc *crtc = pipe_config->base.crtc;
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe, hsw_workaround_pipe;
	enum transcoder cpu_transcoder = pipe_config->cpu_transcoder;
	bool psl_clkgate_wa;

	if (WARN_ON(intel_crtc->active))
		return;

	intel_encoders_pre_pll_enable(intel_crtc, pipe_config, state);

	if (pipe_config->shared_dpll)
		intel_enable_shared_dpll(pipe_config);

	intel_encoders_pre_enable(intel_crtc, pipe_config, state);

	if (intel_crtc_has_dp_encoder(pipe_config))
		intel_dp_set_m_n(pipe_config, M1_N1);

	if (!transcoder_is_dsi(cpu_transcoder))
		intel_set_pipe_timings(pipe_config);

	intel_set_pipe_src_size(pipe_config);

	if (cpu_transcoder != TRANSCODER_EDP &&
	    !transcoder_is_dsi(cpu_transcoder)) {
		I915_WRITE(PIPE_MULT(cpu_transcoder),
			   pipe_config->pixel_multiplier - 1);
	}

	if (pipe_config->has_pch_encoder) {
		intel_cpu_transcoder_set_m_n(pipe_config,
					     &pipe_config->fdi_m_n, NULL);
	}

	if (!transcoder_is_dsi(cpu_transcoder))
		haswell_set_pipeconf(pipe_config);

	if (INTEL_GEN(dev_priv) >= 9 || IS_BROADWELL(dev_priv))
		bdw_set_pipemisc(pipe_config);

	intel_crtc->active = true;

	/* Display WA #1180: WaDisableScalarClockGating: glk, cnl */
	psl_clkgate_wa = (IS_GEMINILAKE(dev_priv) || IS_CANNONLAKE(dev_priv)) &&
			 pipe_config->pch_pfit.enabled;
	if (psl_clkgate_wa)
		glk_pipe_scaler_clock_gating_wa(dev_priv, pipe, true);

	if (INTEL_GEN(dev_priv) >= 9)
		skylake_pfit_enable(pipe_config);
	else
		ironlake_pfit_enable(pipe_config);

	/*
	 * On ILK+ LUT must be loaded before the pipe is running but with
	 * clocks enabled
	 */
	intel_color_load_luts(pipe_config);
	intel_color_commit(pipe_config);
	/* update DSPCNTR to configure gamma/csc for pipe bottom color */
	if (INTEL_GEN(dev_priv) < 9)
		intel_disable_primary_plane(pipe_config);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_set_pipe_chicken(intel_crtc);

	intel_ddi_set_pipe_settings(pipe_config);
	if (!transcoder_is_dsi(cpu_transcoder))
		intel_ddi_enable_transcoder_func(pipe_config);

	if (dev_priv->display.initial_watermarks != NULL)
		dev_priv->display.initial_watermarks(state, pipe_config);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_pipe_mbus_enable(intel_crtc);

	/* XXX: Do the pipe assertions at the right place for BXT DSI. */
	if (!transcoder_is_dsi(cpu_transcoder))
		intel_enable_pipe(pipe_config);

	if (pipe_config->has_pch_encoder)
		lpt_pch_enable(state, pipe_config);

	if (intel_crtc_has_type(pipe_config, INTEL_OUTPUT_DP_MST))
		intel_ddi_set_vc_payload_alloc(pipe_config, true);

	assert_vblank_disabled(crtc);
	intel_crtc_vblank_on(pipe_config);

	intel_encoders_enable(intel_crtc, pipe_config, state);

	if (psl_clkgate_wa) {
		intel_wait_for_vblank(dev_priv, pipe);
		glk_pipe_scaler_clock_gating_wa(dev_priv, pipe, false);
	}

	/* If we change the relative order between pipe/planes enabling, we need
	 * to change the workaround. */
	hsw_workaround_pipe = pipe_config->hsw_workaround_pipe;
	if (IS_HASWELL(dev_priv) && hsw_workaround_pipe != INVALID_PIPE) {
		intel_wait_for_vblank(dev_priv, hsw_workaround_pipe);
		intel_wait_for_vblank(dev_priv, hsw_workaround_pipe);
	}
}