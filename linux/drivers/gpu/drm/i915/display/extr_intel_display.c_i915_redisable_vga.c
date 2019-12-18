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
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_DOMAIN_VGA ; 
 int /*<<< orphan*/  i915_redisable_vga_power_on (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i915_redisable_vga(struct drm_i915_private *dev_priv)
{
	intel_wakeref_t wakeref;

	/*
	 * This function can be called both from intel_modeset_setup_hw_state or
	 * at a very early point in our resume sequence, where the power well
	 * structures are not yet restored. Since this function is at a very
	 * paranoid "someone might have enabled VGA while we were not looking"
	 * level, just check if the power well is enabled instead of trying to
	 * follow the "don't touch the power well if we don't need it" policy
	 * the rest of the driver uses.
	 */
	wakeref = intel_display_power_get_if_enabled(dev_priv,
						     POWER_DOMAIN_VGA);
	if (!wakeref)
		return;

	i915_redisable_vga_power_on(dev_priv);

	intel_display_power_put(dev_priv, POWER_DOMAIN_VGA, wakeref);
}