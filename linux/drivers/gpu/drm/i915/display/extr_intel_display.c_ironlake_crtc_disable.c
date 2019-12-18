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
typedef  int u32 ;
struct TYPE_2__ {struct drm_crtc* crtc; } ;
struct intel_crtc_state {scalar_t__ has_pch_encoder; TYPE_1__ base; } ;
struct intel_crtc {int pipe; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCH_DPLL_SEL ; 
 int TRANS_DPLLB_SEL (int) ; 
 int TRANS_DPLL_ENABLE (int) ; 
 int /*<<< orphan*/  TRANS_DP_CTL (int) ; 
 int TRANS_DP_OUTPUT_ENABLE ; 
 int TRANS_DP_PORT_SEL_MASK ; 
 int TRANS_DP_PORT_SEL_NONE ; 
 int /*<<< orphan*/  assert_vblank_disabled (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  intel_disable_pipe (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_encoders_disable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_post_disable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  intel_set_pch_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  ironlake_disable_pch_transcoder (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  ironlake_fdi_disable (struct drm_crtc*) ; 
 int /*<<< orphan*/  ironlake_fdi_pll_disable (struct intel_crtc*) ; 
 int /*<<< orphan*/  ironlake_pfit_disable (struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void ironlake_crtc_disable(struct intel_crtc_state *old_crtc_state,
				  struct intel_atomic_state *state)
{
	struct drm_crtc *crtc = old_crtc_state->base.crtc;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;

	/*
	 * Sometimes spurious CPU pipe underruns happen when the
	 * pipe is already disabled, but FDI RX/TX is still enabled.
	 * Happens at least with VGA+HDMI cloning. Suppress them.
	 */
	intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, false);
	intel_set_pch_fifo_underrun_reporting(dev_priv, pipe, false);

	intel_encoders_disable(intel_crtc, old_crtc_state, state);

	drm_crtc_vblank_off(crtc);
	assert_vblank_disabled(crtc);

	intel_disable_pipe(old_crtc_state);

	ironlake_pfit_disable(old_crtc_state);

	if (old_crtc_state->has_pch_encoder)
		ironlake_fdi_disable(crtc);

	intel_encoders_post_disable(intel_crtc, old_crtc_state, state);

	if (old_crtc_state->has_pch_encoder) {
		ironlake_disable_pch_transcoder(dev_priv, pipe);

		if (HAS_PCH_CPT(dev_priv)) {
			i915_reg_t reg;
			u32 temp;

			/* disable TRANS_DP_CTL */
			reg = TRANS_DP_CTL(pipe);
			temp = I915_READ(reg);
			temp &= ~(TRANS_DP_OUTPUT_ENABLE |
				  TRANS_DP_PORT_SEL_MASK);
			temp |= TRANS_DP_PORT_SEL_NONE;
			I915_WRITE(reg, temp);

			/* disable DPLL_SEL */
			temp = I915_READ(PCH_DPLL_SEL);
			temp &= ~(TRANS_DPLL_ENABLE(pipe) | TRANS_DPLLB_SEL(pipe));
			I915_WRITE(PCH_DPLL_SEL, temp);
		}

		ironlake_fdi_pll_disable(intel_crtc);
	}

	intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, true);
	intel_set_pch_fifo_underrun_reporting(dev_priv, pipe, true);
}