#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  rawclk_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 

__attribute__((used)) static u32 g4x_get_aux_clock_divider(struct intel_dp *intel_dp, int index)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);

	if (index)
		return 0;

	/*
	 * The clock divider is based off the hrawclk, and would like to run at
	 * 2MHz.  So, take the hrawclk value and divide by 2000 and use that
	 */
	return DIV_ROUND_CLOSEST(dev_priv->rawclk_freq, 2000);
}