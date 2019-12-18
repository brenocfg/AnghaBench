#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  uc; } ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ contexts; TYPE_1__ gt; int /*<<< orphan*/  gt_wa_list; TYPE_3__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  i915_gem_cleanup_userptr (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_contexts_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_fini_scratch (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_cleanup_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_engines_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_timelines_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_cleanup_firmwares (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_wa_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void i915_gem_driver_release(struct drm_i915_private *dev_priv)
{
	mutex_lock(&dev_priv->drm.struct_mutex);
	intel_engines_cleanup(dev_priv);
	i915_gem_contexts_fini(dev_priv);
	i915_gem_fini_scratch(dev_priv);
	mutex_unlock(&dev_priv->drm.struct_mutex);

	intel_wa_list_free(&dev_priv->gt_wa_list);

	intel_cleanup_gt_powersave(dev_priv);

	intel_uc_cleanup_firmwares(&dev_priv->gt.uc);
	i915_gem_cleanup_userptr(dev_priv);
	intel_timelines_fini(dev_priv);

	i915_gem_drain_freed_objects(dev_priv);

	WARN_ON(!list_empty(&dev_priv->contexts.list));
}