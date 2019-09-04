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
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_driver_cleanup_early (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kfree (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void i915_driver_release(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);

	i915_driver_cleanup_early(dev_priv);
	drm_dev_fini(&dev_priv->drm);

	kfree(dev_priv);
}