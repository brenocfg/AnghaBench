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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; int /*<<< orphan*/  config; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL (int) ; 
 int DPLL_DVO_2X_MODE ; 
 int DPLL_VGA_MODE_DIS ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DVO ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 int PIPE_A ; 
 int PIPE_B ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_pipe_disabled (struct drm_i915_private*,int) ; 
 scalar_t__ intel_crtc_has_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_num_dvo_pipes (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_disable_pll(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;

	/* Disable DVO 2x clock on both PLLs if necessary */
	if (IS_I830(dev_priv) &&
	    intel_crtc_has_type(crtc->config, INTEL_OUTPUT_DVO) &&
	    !intel_num_dvo_pipes(dev_priv)) {
		I915_WRITE(DPLL(PIPE_B),
			   I915_READ(DPLL(PIPE_B)) & ~DPLL_DVO_2X_MODE);
		I915_WRITE(DPLL(PIPE_A),
			   I915_READ(DPLL(PIPE_A)) & ~DPLL_DVO_2X_MODE);
	}

	/* Don't disable pipe or pipe PLLs if needed */
	if (IS_I830(dev_priv))
		return;

	/* Make sure the pipe isn't still relying on us */
	assert_pipe_disabled(dev_priv, pipe);

	I915_WRITE(DPLL(pipe), DPLL_VGA_MODE_DIS);
	POSTING_READ(DPLL(pipe));
}