#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {struct drm_crtc* crtc; } ;
struct intel_crtc_state {int hsw_workaround_pipe; TYPE_5__ base; } ;
struct intel_crtc {int pipe; int active; TYPE_3__* config; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* initial_watermarks ) (struct intel_atomic_state*,struct intel_crtc_state*) ;} ;
struct drm_i915_private {TYPE_2__ display; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct drm_atomic_state {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
struct TYPE_7__ {scalar_t__ enabled; } ;
struct TYPE_9__ {int cpu_transcoder; scalar_t__ has_pch_encoder; TYPE_1__ pch_pfit; int /*<<< orphan*/  fdi_m_n; scalar_t__ pixel_multiplier; scalar_t__ shared_dpll; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DP_MST ; 
 int INVALID_PIPE ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  M1_N1 ; 
 int PER_PIXEL_ALPHA_BYPASS_EN ; 
 int /*<<< orphan*/  PIPE_CHICKEN (int) ; 
 int /*<<< orphan*/  PIPE_MULT (int) ; 
 int TRANSCODER_EDP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_vblank_disabled (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  glk_pipe_scaler_clock_gating_wa (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  haswell_set_pipeconf (struct drm_crtc*) ; 
 int /*<<< orphan*/  haswell_set_pipemisc (struct drm_crtc*) ; 
 int /*<<< orphan*/  icl_map_plls_to_ports (struct drm_crtc*,struct intel_crtc_state*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  icl_pipe_mbus_enable (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_color_load_luts (TYPE_5__*) ; 
 int /*<<< orphan*/  intel_color_set_csc (TYPE_5__*) ; 
 int /*<<< orphan*/  intel_cpu_transcoder_set_m_n (struct intel_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ intel_crtc_has_dp_encoder (TYPE_3__*) ; 
 scalar_t__ intel_crtc_has_type (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_enable_transcoder_func (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_ddi_set_pipe_settings (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_ddi_set_vc_payload_alloc (struct intel_crtc_state*,int) ; 
 int /*<<< orphan*/  intel_dp_set_m_n (struct intel_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_enable_pipe (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_enable_shared_dpll (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_encoders_enable (struct drm_crtc*,struct intel_crtc_state*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_pre_enable (struct drm_crtc*,struct intel_crtc_state*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_pre_pll_enable (struct drm_crtc*,struct intel_crtc_state*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  intel_set_pipe_src_size (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_set_pipe_timings (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  ironlake_pfit_enable (struct intel_crtc*) ; 
 int /*<<< orphan*/  lpt_pch_enable (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  skylake_pfit_enable (struct intel_crtc*) ; 
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  transcoder_is_dsi (int) ; 

__attribute__((used)) static void haswell_crtc_enable(struct intel_crtc_state *pipe_config,
				struct drm_atomic_state *old_state)
{
	struct drm_crtc *crtc = pipe_config->base.crtc;
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe, hsw_workaround_pipe;
	enum transcoder cpu_transcoder = intel_crtc->config->cpu_transcoder;
	struct intel_atomic_state *old_intel_state =
		to_intel_atomic_state(old_state);
	bool psl_clkgate_wa;
	u32 pipe_chicken;

	if (WARN_ON(intel_crtc->active))
		return;

	intel_encoders_pre_pll_enable(crtc, pipe_config, old_state);

	if (intel_crtc->config->shared_dpll)
		intel_enable_shared_dpll(intel_crtc);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_map_plls_to_ports(crtc, pipe_config, old_state);

	intel_encoders_pre_enable(crtc, pipe_config, old_state);

	if (intel_crtc_has_dp_encoder(intel_crtc->config))
		intel_dp_set_m_n(intel_crtc, M1_N1);

	if (!transcoder_is_dsi(cpu_transcoder))
		intel_set_pipe_timings(intel_crtc);

	intel_set_pipe_src_size(intel_crtc);

	if (cpu_transcoder != TRANSCODER_EDP &&
	    !transcoder_is_dsi(cpu_transcoder)) {
		I915_WRITE(PIPE_MULT(cpu_transcoder),
			   intel_crtc->config->pixel_multiplier - 1);
	}

	if (intel_crtc->config->has_pch_encoder) {
		intel_cpu_transcoder_set_m_n(intel_crtc,
				     &intel_crtc->config->fdi_m_n, NULL);
	}

	if (!transcoder_is_dsi(cpu_transcoder))
		haswell_set_pipeconf(crtc);

	haswell_set_pipemisc(crtc);

	intel_color_set_csc(&pipe_config->base);

	intel_crtc->active = true;

	/* Display WA #1180: WaDisableScalarClockGating: glk, cnl */
	psl_clkgate_wa = (IS_GEMINILAKE(dev_priv) || IS_CANNONLAKE(dev_priv)) &&
			 intel_crtc->config->pch_pfit.enabled;
	if (psl_clkgate_wa)
		glk_pipe_scaler_clock_gating_wa(dev_priv, pipe, true);

	if (INTEL_GEN(dev_priv) >= 9)
		skylake_pfit_enable(intel_crtc);
	else
		ironlake_pfit_enable(intel_crtc);

	/*
	 * On ILK+ LUT must be loaded before the pipe is running but with
	 * clocks enabled
	 */
	intel_color_load_luts(&pipe_config->base);

	/*
	 * Display WA #1153: enable hardware to bypass the alpha math
	 * and rounding for per-pixel values 00 and 0xff
	 */
	if (INTEL_GEN(dev_priv) >= 11) {
		pipe_chicken = I915_READ(PIPE_CHICKEN(pipe));
		if (!(pipe_chicken & PER_PIXEL_ALPHA_BYPASS_EN))
			I915_WRITE_FW(PIPE_CHICKEN(pipe),
				      pipe_chicken | PER_PIXEL_ALPHA_BYPASS_EN);
	}

	intel_ddi_set_pipe_settings(pipe_config);
	if (!transcoder_is_dsi(cpu_transcoder))
		intel_ddi_enable_transcoder_func(pipe_config);

	if (dev_priv->display.initial_watermarks != NULL)
		dev_priv->display.initial_watermarks(old_intel_state, pipe_config);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_pipe_mbus_enable(intel_crtc);

	/* XXX: Do the pipe assertions at the right place for BXT DSI. */
	if (!transcoder_is_dsi(cpu_transcoder))
		intel_enable_pipe(pipe_config);

	if (intel_crtc->config->has_pch_encoder)
		lpt_pch_enable(old_intel_state, pipe_config);

	if (intel_crtc_has_type(intel_crtc->config, INTEL_OUTPUT_DP_MST))
		intel_ddi_set_vc_payload_alloc(pipe_config, true);

	assert_vblank_disabled(crtc);
	drm_crtc_vblank_on(crtc);

	intel_encoders_enable(crtc, pipe_config, old_state);

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