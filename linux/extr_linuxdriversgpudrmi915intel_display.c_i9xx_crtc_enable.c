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
struct TYPE_4__ {struct drm_crtc* crtc; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct intel_crtc {int pipe; int active; int /*<<< orphan*/  config; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* initial_watermarks ) (struct intel_atomic_state*,int /*<<< orphan*/ ) ;} ;
struct drm_i915_private {TYPE_1__ display; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_atomic_state {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  IS_GEN2 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  M1_N1 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_vblank_disabled (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  i9xx_enable_pll (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  i9xx_pfit_enable (struct intel_crtc*) ; 
 int /*<<< orphan*/  i9xx_set_pipeconf (struct intel_crtc*) ; 
 int /*<<< orphan*/  i9xx_set_pll_dividers (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_color_load_luts (TYPE_2__*) ; 
 scalar_t__ intel_crtc_has_dp_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_set_m_n (struct intel_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_enable_pipe (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_encoders_enable (struct drm_crtc*,struct intel_crtc_state*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_pre_enable (struct drm_crtc*,struct intel_crtc_state*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  intel_set_pipe_src_size (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_set_pipe_timings (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_update_watermarks (struct intel_crtc*) ; 
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void i9xx_crtc_enable(struct intel_crtc_state *pipe_config,
			     struct drm_atomic_state *old_state)
{
	struct intel_atomic_state *old_intel_state =
		to_intel_atomic_state(old_state);
	struct drm_crtc *crtc = pipe_config->base.crtc;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	enum pipe pipe = intel_crtc->pipe;

	if (WARN_ON(intel_crtc->active))
		return;

	i9xx_set_pll_dividers(intel_crtc);

	if (intel_crtc_has_dp_encoder(intel_crtc->config))
		intel_dp_set_m_n(intel_crtc, M1_N1);

	intel_set_pipe_timings(intel_crtc);
	intel_set_pipe_src_size(intel_crtc);

	i9xx_set_pipeconf(intel_crtc);

	intel_crtc->active = true;

	if (!IS_GEN2(dev_priv))
		intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, true);

	intel_encoders_pre_enable(crtc, pipe_config, old_state);

	i9xx_enable_pll(intel_crtc, pipe_config);

	i9xx_pfit_enable(intel_crtc);

	intel_color_load_luts(&pipe_config->base);

	if (dev_priv->display.initial_watermarks != NULL)
		dev_priv->display.initial_watermarks(old_intel_state,
						     intel_crtc->config);
	else
		intel_update_watermarks(intel_crtc);
	intel_enable_pipe(pipe_config);

	assert_vblank_disabled(crtc);
	drm_crtc_vblank_on(crtc);

	intel_encoders_enable(crtc, pipe_config, old_state);
}