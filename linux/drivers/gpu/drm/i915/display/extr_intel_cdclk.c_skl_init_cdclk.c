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
struct intel_cdclk_state {scalar_t__ cdclk; scalar_t__ vco; int /*<<< orphan*/  voltage_level; } ;
struct TYPE_2__ {struct intel_cdclk_state hw; } ;
struct drm_i915_private {scalar_t__ skl_preferred_vco_freq; TYPE_1__ cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_PIPE ; 
 scalar_t__ skl_calc_cdclk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skl_calc_voltage_level (scalar_t__) ; 
 int /*<<< orphan*/  skl_sanitize_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  skl_set_cdclk (struct drm_i915_private*,struct intel_cdclk_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_set_preferred_cdclk_vco (struct drm_i915_private*,scalar_t__) ; 

__attribute__((used)) static void skl_init_cdclk(struct drm_i915_private *dev_priv)
{
	struct intel_cdclk_state cdclk_state;

	skl_sanitize_cdclk(dev_priv);

	if (dev_priv->cdclk.hw.cdclk != 0 &&
	    dev_priv->cdclk.hw.vco != 0) {
		/*
		 * Use the current vco as our initial
		 * guess as to what the preferred vco is.
		 */
		if (dev_priv->skl_preferred_vco_freq == 0)
			skl_set_preferred_cdclk_vco(dev_priv,
						    dev_priv->cdclk.hw.vco);
		return;
	}

	cdclk_state = dev_priv->cdclk.hw;

	cdclk_state.vco = dev_priv->skl_preferred_vco_freq;
	if (cdclk_state.vco == 0)
		cdclk_state.vco = 8100000;
	cdclk_state.cdclk = skl_calc_cdclk(0, cdclk_state.vco);
	cdclk_state.voltage_level = skl_calc_voltage_level(cdclk_state.cdclk);

	skl_set_cdclk(dev_priv, &cdclk_state, INVALID_PIPE);
}