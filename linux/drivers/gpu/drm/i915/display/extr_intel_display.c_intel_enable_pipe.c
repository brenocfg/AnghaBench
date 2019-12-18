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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int cpu_transcoder; scalar_t__ has_pch_encoder; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DSI ; 
 int /*<<< orphan*/  IS_I830 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_ENABLE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  assert_dsi_pll_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  assert_fdi_rx_pll_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_fdi_tx_pll_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_planes_disabled (struct intel_crtc*) ; 
 int /*<<< orphan*/  assert_pll_enabled (struct drm_i915_private*,int) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_crtc_max_vblank_count (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_crtc_pch_transcoder (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_wait_for_pipe_scanline_moving (struct intel_crtc*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_intel_pipe_enable (struct intel_crtc*) ; 

__attribute__((used)) static void intel_enable_pipe(const struct intel_crtc_state *new_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(new_crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum transcoder cpu_transcoder = new_crtc_state->cpu_transcoder;
	enum pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 val;

	DRM_DEBUG_KMS("enabling pipe %c\n", pipe_name(pipe));

	assert_planes_disabled(crtc);

	/*
	 * A pipe without a PLL won't actually be able to drive bits from
	 * a plane.  On ILK+ the pipe PLLs are integrated, so we don't
	 * need the check.
	 */
	if (HAS_GMCH(dev_priv)) {
		if (intel_crtc_has_type(new_crtc_state, INTEL_OUTPUT_DSI))
			assert_dsi_pll_enabled(dev_priv);
		else
			assert_pll_enabled(dev_priv, pipe);
	} else {
		if (new_crtc_state->has_pch_encoder) {
			/* if driving the PCH, we need FDI enabled */
			assert_fdi_rx_pll_enabled(dev_priv,
						  intel_crtc_pch_transcoder(crtc));
			assert_fdi_tx_pll_enabled(dev_priv,
						  (enum pipe) cpu_transcoder);
		}
		/* FIXME: assert CPU port conditions for SNB+ */
	}

	trace_intel_pipe_enable(crtc);

	reg = PIPECONF(cpu_transcoder);
	val = I915_READ(reg);
	if (val & PIPECONF_ENABLE) {
		/* we keep both pipes enabled on 830 */
		WARN_ON(!IS_I830(dev_priv));
		return;
	}

	I915_WRITE(reg, val | PIPECONF_ENABLE);
	POSTING_READ(reg);

	/*
	 * Until the pipe starts PIPEDSL reads will return a stale value,
	 * which causes an apparent vblank timestamp jump when PIPEDSL
	 * resets to its proper value. That also messes up the frame count
	 * when it's derived from the timestamps. So let's wait for the
	 * pipe to start properly before we call drm_crtc_vblank_on()
	 */
	if (intel_crtc_max_vblank_count(new_crtc_state) == 0)
		intel_wait_for_pipe_scanline_moving(crtc);
}