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
struct intel_cdclk_state {unsigned int cdclk; unsigned int vco; int /*<<< orphan*/  voltage_level; } ;
struct TYPE_3__ {unsigned int vco; int /*<<< orphan*/  voltage_level; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  CDCLK_CTL ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int ICL_CDCLK_CD2X_PIPE_NONE ; 
 int /*<<< orphan*/  SKL_CDCLK_PREPARE_FOR_CHANGE ; 
 int /*<<< orphan*/  SKL_CDCLK_READY_FOR_CHANGE ; 
 int /*<<< orphan*/  SKL_PCODE_CDCLK_CONTROL ; 
 int /*<<< orphan*/  cnl_cdclk_pll_disable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_cdclk_pll_enable (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  intel_update_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  sandybridge_pcode_write (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skl_cdclk_decimal (unsigned int) ; 
 int skl_pcode_request (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void icl_set_cdclk(struct drm_i915_private *dev_priv,
			  const struct intel_cdclk_state *cdclk_state,
			  enum pipe pipe)
{
	unsigned int cdclk = cdclk_state->cdclk;
	unsigned int vco = cdclk_state->vco;
	int ret;

	ret = skl_pcode_request(dev_priv, SKL_PCODE_CDCLK_CONTROL,
				SKL_CDCLK_PREPARE_FOR_CHANGE,
				SKL_CDCLK_READY_FOR_CHANGE,
				SKL_CDCLK_READY_FOR_CHANGE, 3);
	if (ret) {
		DRM_ERROR("Failed to inform PCU about cdclk change (%d)\n",
			  ret);
		return;
	}

	if (dev_priv->cdclk.hw.vco != 0 &&
	    dev_priv->cdclk.hw.vco != vco)
		cnl_cdclk_pll_disable(dev_priv);

	if (dev_priv->cdclk.hw.vco != vco)
		cnl_cdclk_pll_enable(dev_priv, vco);

	/*
	 * On ICL CD2X_DIV can only be 1, so we'll never end up changing the
	 * divider here synchronized to a pipe while CDCLK is on, nor will we
	 * need the corresponding vblank wait.
	 */
	I915_WRITE(CDCLK_CTL, ICL_CDCLK_CD2X_PIPE_NONE |
			      skl_cdclk_decimal(cdclk));

	sandybridge_pcode_write(dev_priv, SKL_PCODE_CDCLK_CONTROL,
				cdclk_state->voltage_level);

	intel_update_cdclk(dev_priv);

	/*
	 * Can't read out the voltage level :(
	 * Let's just assume everything is as expected.
	 */
	dev_priv->cdclk.hw.voltage_level = cdclk_state->voltage_level;
}