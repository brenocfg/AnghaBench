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
struct intel_runtime_pm {int dummy; } ;
struct drm_i915_private {struct intel_runtime_pm runtime_pm; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  i915_driver_destroy (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_late_release (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_mmio_release (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_driver_release (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_ggtt_driver_release (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_driver_release (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  intel_sanitize_gt_powersave (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void i915_driver_release(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_runtime_pm *rpm = &dev_priv->runtime_pm;

	disable_rpm_wakeref_asserts(rpm);

	i915_gem_driver_release(dev_priv);

	i915_ggtt_driver_release(dev_priv);

	/* Paranoia: make sure we have disabled everything before we exit. */
	intel_sanitize_gt_powersave(dev_priv);

	i915_driver_mmio_release(dev_priv);

	enable_rpm_wakeref_asserts(rpm);
	intel_runtime_pm_driver_release(rpm);

	i915_driver_late_release(dev_priv);
	i915_driver_destroy(dev_priv);
}