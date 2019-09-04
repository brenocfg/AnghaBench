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
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ contexts; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  i915_gem_cleanup_engines (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_userptr (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_contexts_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_drain_workqueue (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_suspend_late (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_fini_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_fini_misc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void i915_gem_fini(struct drm_i915_private *dev_priv)
{
	i915_gem_suspend_late(dev_priv);

	/* Flush any outstanding unpin_work. */
	i915_gem_drain_workqueue(dev_priv);

	mutex_lock(&dev_priv->drm.struct_mutex);
	intel_uc_fini_hw(dev_priv);
	intel_uc_fini(dev_priv);
	i915_gem_cleanup_engines(dev_priv);
	i915_gem_contexts_fini(dev_priv);
	mutex_unlock(&dev_priv->drm.struct_mutex);

	intel_uc_fini_misc(dev_priv);
	i915_gem_cleanup_userptr(dev_priv);

	i915_gem_drain_freed_objects(dev_priv);

	WARN_ON(!list_empty(&dev_priv->contexts.list));
}