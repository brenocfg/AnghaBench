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
struct intel_cdclk_state {int /*<<< orphan*/  cdclk; int /*<<< orphan*/  voltage_level; scalar_t__ vco; int /*<<< orphan*/  bypass; } ;
struct TYPE_2__ {struct intel_cdclk_state hw; } ;
struct drm_i915_private {TYPE_1__ cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_PIPE ; 
 int /*<<< orphan*/  icl_calc_voltage_level (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_set_cdclk (struct drm_i915_private*,struct intel_cdclk_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_uninit_cdclk(struct drm_i915_private *dev_priv)
{
	struct intel_cdclk_state cdclk_state = dev_priv->cdclk.hw;

	cdclk_state.cdclk = cdclk_state.bypass;
	cdclk_state.vco = 0;
	cdclk_state.voltage_level = icl_calc_voltage_level(dev_priv,
							   cdclk_state.cdclk);

	icl_set_cdclk(dev_priv, &cdclk_state, INVALID_PIPE);
}