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
struct intel_dp {int /*<<< orphan*/  DP; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_A ; 
 int /*<<< orphan*/  DP_PLL_ENABLE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_dp_port_disabled (struct intel_dp*) ; 
 int /*<<< orphan*/  assert_edp_pll_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  assert_pipe_disabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ironlake_edp_pll_off(struct intel_dp *intel_dp,
				 const struct intel_crtc_state *old_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(old_crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);

	assert_pipe_disabled(dev_priv, crtc->pipe);
	assert_dp_port_disabled(intel_dp);
	assert_edp_pll_enabled(dev_priv);

	DRM_DEBUG_KMS("disabling eDP PLL\n");

	intel_dp->DP &= ~DP_PLL_ENABLE;

	I915_WRITE(DP_A, intel_dp->DP);
	POSTING_READ(DP_A);
	udelay(200);
}