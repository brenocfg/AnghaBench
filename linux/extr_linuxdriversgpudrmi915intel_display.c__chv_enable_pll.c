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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dpll; } ;
struct intel_crtc_state {TYPE_1__ dpll_hw_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_2__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  sb_lock; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum dpio_channel { ____Placeholder_dpio_channel } dpio_channel ;

/* Variables and functions */
 int /*<<< orphan*/  CHV_CMN_DW14 (int) ; 
 int /*<<< orphan*/  DPIO_DCLKP_EN ; 
 int /*<<< orphan*/  DPLL (int) ; 
 int /*<<< orphan*/  DPLL_LOCK_VLV ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vlv_dpio_read (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_dpio_write (struct drm_i915_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vlv_pipe_to_channel (int) ; 

__attribute__((used)) static void _chv_enable_pll(struct intel_crtc *crtc,
			    const struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;
	enum dpio_channel port = vlv_pipe_to_channel(pipe);
	u32 tmp;

	mutex_lock(&dev_priv->sb_lock);

	/* Enable back the 10bit clock to display controller */
	tmp = vlv_dpio_read(dev_priv, pipe, CHV_CMN_DW14(port));
	tmp |= DPIO_DCLKP_EN;
	vlv_dpio_write(dev_priv, pipe, CHV_CMN_DW14(port), tmp);

	mutex_unlock(&dev_priv->sb_lock);

	/*
	 * Need to wait > 100ns between dclkp clock enable bit and PLL enable.
	 */
	udelay(1);

	/* Enable PLL */
	I915_WRITE(DPLL(pipe), pipe_config->dpll_hw_state.dpll);

	/* Check PLL is locked */
	if (intel_wait_for_register(dev_priv,
				    DPLL(pipe), DPLL_LOCK_VLV, DPLL_LOCK_VLV,
				    1))
		DRM_ERROR("PLL %d failed to lock\n", pipe);
}