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
struct TYPE_3__ {int ref; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 

int cnl_hdmi_pll_ref_clock(struct drm_i915_private *dev_priv)
{
	int ref_clock = dev_priv->cdclk.hw.ref;

	/*
	 * For ICL+, the spec states: if reference frequency is 38.4,
	 * use 19.2 because the DPLL automatically divides that by 2.
	 */
	if (INTEL_GEN(dev_priv) >= 11 && ref_clock == 38400)
		ref_clock = 19200;

	return ref_clock;
}