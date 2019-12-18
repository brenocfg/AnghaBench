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
struct i915_power_domains {int /*<<< orphan*/  wakeref; } ;
struct drm_i915_private {struct i915_power_domains power_domains; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_DOMAIN_INIT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_power_domains_verify_state (struct drm_i915_private*) ; 

void intel_power_domains_disable(struct drm_i915_private *i915)
{
	struct i915_power_domains *power_domains = &i915->power_domains;

	WARN_ON(power_domains->wakeref);
	power_domains->wakeref =
		intel_display_power_get(i915, POWER_DOMAIN_INIT);

	intel_power_domains_verify_state(i915);
}