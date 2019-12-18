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
struct TYPE_2__ {struct drm_crtc* crtc; } ;
struct intel_crtc_state {int cpu_transcoder; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DP_MST ; 
 int /*<<< orphan*/  assert_vblank_disabled (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_disable_transcoder_func (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_ddi_set_vc_payload_alloc (struct intel_crtc_state*,int) ; 
 int /*<<< orphan*/  intel_disable_pipe (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_dsc_disable (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_encoders_disable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_post_disable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  intel_encoders_post_pll_disable (struct intel_crtc*,struct intel_crtc_state*,struct intel_atomic_state*) ; 
 int /*<<< orphan*/  ironlake_pfit_disable (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  skylake_scaler_disable (struct intel_crtc*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  transcoder_is_dsi (int) ; 

__attribute__((used)) static void haswell_crtc_disable(struct intel_crtc_state *old_crtc_state,
				 struct intel_atomic_state *state)
{
	struct drm_crtc *crtc = old_crtc_state->base.crtc;
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	enum transcoder cpu_transcoder = old_crtc_state->cpu_transcoder;

	intel_encoders_disable(intel_crtc, old_crtc_state, state);

	drm_crtc_vblank_off(crtc);
	assert_vblank_disabled(crtc);

	/* XXX: Do the pipe assertions at the right place for BXT DSI. */
	if (!transcoder_is_dsi(cpu_transcoder))
		intel_disable_pipe(old_crtc_state);

	if (intel_crtc_has_type(old_crtc_state, INTEL_OUTPUT_DP_MST))
		intel_ddi_set_vc_payload_alloc(old_crtc_state, false);

	if (!transcoder_is_dsi(cpu_transcoder))
		intel_ddi_disable_transcoder_func(old_crtc_state);

	intel_dsc_disable(old_crtc_state);

	if (INTEL_GEN(dev_priv) >= 9)
		skylake_scaler_disable(intel_crtc);
	else
		ironlake_pfit_disable(old_crtc_state);

	intel_encoders_post_disable(intel_crtc, old_crtc_state, state);

	intel_encoders_post_pll_disable(intel_crtc, old_crtc_state, state);
}