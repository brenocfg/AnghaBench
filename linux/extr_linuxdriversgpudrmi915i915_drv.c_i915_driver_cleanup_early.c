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

/* Variables and functions */
 int /*<<< orphan*/  i915_engines_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_early (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_workqueues_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_irq_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_cleanup_early (struct drm_i915_private*) ; 

__attribute__((used)) static void i915_driver_cleanup_early(struct drm_i915_private *dev_priv)
{
	intel_irq_fini(dev_priv);
	intel_uc_cleanup_early(dev_priv);
	i915_gem_cleanup_early(dev_priv);
	i915_workqueues_cleanup(dev_priv);
	i915_engines_cleanup(dev_priv);
}