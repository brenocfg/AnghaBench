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
struct TYPE_3__ {int dpll; int dpll_md; } ;
struct intel_crtc_state {TYPE_1__ dpll_hw_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPLL_MD (int /*<<< orphan*/ ) ; 
 int DPLL_VGA_MODE_DIS ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_panel_unlocked (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_pipe_disabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ i9xx_has_pps (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void i9xx_enable_pll(struct intel_crtc *crtc,
			    const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	i915_reg_t reg = DPLL(crtc->pipe);
	u32 dpll = crtc_state->dpll_hw_state.dpll;
	int i;

	assert_pipe_disabled(dev_priv, crtc->pipe);

	/* PLL is protected by panel, make sure we can write it */
	if (i9xx_has_pps(dev_priv))
		assert_panel_unlocked(dev_priv, crtc->pipe);

	/*
	 * Apparently we need to have VGA mode enabled prior to changing
	 * the P1/P2 dividers. Otherwise the DPLL will keep using the old
	 * dividers, even though the register value does change.
	 */
	I915_WRITE(reg, dpll & ~DPLL_VGA_MODE_DIS);
	I915_WRITE(reg, dpll);

	/* Wait for the clocks to stabilize. */
	POSTING_READ(reg);
	udelay(150);

	if (INTEL_GEN(dev_priv) >= 4) {
		I915_WRITE(DPLL_MD(crtc->pipe),
			   crtc_state->dpll_hw_state.dpll_md);
	} else {
		/* The pixel multiplier can only be updated once the
		 * DPLL is enabled and the clocks are stable.
		 *
		 * So write it again.
		 */
		I915_WRITE(reg, dpll);
	}

	/* We do this three times for luck */
	for (i = 0; i < 3; i++) {
		I915_WRITE(reg, dpll);
		POSTING_READ(reg);
		udelay(150); /* wait for warmup */
	}
}