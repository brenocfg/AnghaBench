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
struct intel_crtc_state {scalar_t__ has_pch_encoder; int /*<<< orphan*/  fdi_m_n; TYPE_1__ base; } ;
struct intel_crtc {int pipe; int active; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* initial_watermarks ) (struct intel_atomic_state*,struct intel_crtc_state*) ;} ;
struct drm_i915_private {TYPE_2__ display; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  M1_N1 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_fdi_rx_disabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_fdi_tx_disabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_vblank_disabled (struct drm_crtc*) ; 
 int /*<<< orphan*/  cpt_verify_modeset (struct drm_device*,int) ; 
 int /*<<< orphan*/  intel_color_commit (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_color_load_luts (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_cpu_transcoder_set_m_n (struct intel_crtc_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_crtc_vblank_on (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_disable_primary_plane (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_dp_set_m_n (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_enable_pipe (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_encoders_enable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_pre_enable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_prepare_shared_dpll (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  intel_set_pch_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  intel_set_pipe_src_size (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_set_pipe_timings (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  ironlake_fdi_pll_enable (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  ironlake_pch_enable (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  ironlake_pfit_enable (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  ironlake_set_pipeconf (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void ironlake_crtc_enable(struct intel_crtc_state *pipe_config,
				 struct intel_atomic_state *state)
{
	struct drm_crtc *crtc = pipe_config->base.crtc;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;

	if (WARN_ON(intel_crtc->active))
		return;

	/*
	 * Sometimes spurious CPU pipe underruns happen during FDI
	 * training, at least with VGA+HDMI cloning. Suppress them.
	 *
	 * On ILK we get an occasional spurious CPU pipe underruns
	 * between eDP port A enable and vdd enable. Also PCH port
	 * enable seems to result in the occasional CPU pipe underrun.
	 *
	 * Spurious PCH underruns also occur during PCH enabling.
	 */
	intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, false);
	intel_set_pch_fifo_underrun_reporting(dev_priv, pipe, false);

	if (pipe_config->has_pch_encoder)
		intel_prepare_shared_dpll(pipe_config);

	if (intel_crtc_has_dp_encoder(pipe_config))
		intel_dp_set_m_n(pipe_config, M1_N1);

	intel_set_pipe_timings(pipe_config);
	intel_set_pipe_src_size(pipe_config);

	if (pipe_config->has_pch_encoder) {
		intel_cpu_transcoder_set_m_n(pipe_config,
					     &pipe_config->fdi_m_n, NULL);
	}

	ironlake_set_pipeconf(pipe_config);

	intel_crtc->active = true;

	intel_encoders_pre_enable(intel_crtc, pipe_config, state);

	if (pipe_config->has_pch_encoder) {
		/* Note: FDI PLL enabling _must_ be done before we enable the
		 * cpu pipes, hence this is separate from all the other fdi/pch
		 * enabling. */
		ironlake_fdi_pll_enable(pipe_config);
	} else {
		assert_fdi_tx_disabled(dev_priv, pipe);
		assert_fdi_rx_disabled(dev_priv, pipe);
	}

	ironlake_pfit_enable(pipe_config);

	/*
	 * On ILK+ LUT must be loaded before the pipe is running but with
	 * clocks enabled
	 */
	intel_color_load_luts(pipe_config);
	intel_color_commit(pipe_config);
	/* update DSPCNTR to configure gamma for pipe bottom color */
	intel_disable_primary_plane(pipe_config);

	if (dev_priv->display.initial_watermarks != NULL)
		dev_priv->display.initial_watermarks(state, pipe_config);
	intel_enable_pipe(pipe_config);

	if (pipe_config->has_pch_encoder)
		ironlake_pch_enable(state, pipe_config);

	assert_vblank_disabled(crtc);
	intel_crtc_vblank_on(pipe_config);

	intel_encoders_enable(intel_crtc, pipe_config, state);

	if (HAS_PCH_CPT(dev_priv))
		cpt_verify_modeset(dev, intel_crtc->pipe);

	/*
	 * Must wait for vblank to avoid spurious PCH FIFO underruns.
	 * And a second vblank wait is needed at least on ILK with
	 * some interlaced HDMI modes. Let's do the double wait always
	 * in case there are more corner cases we don't know about.
	 */
	if (pipe_config->has_pch_encoder) {
		intel_wait_for_vblank(dev_priv, pipe);
		intel_wait_for_vblank(dev_priv, pipe);
	}
	intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, true);
	intel_set_pch_fifo_underrun_reporting(dev_priv, pipe, true);
}