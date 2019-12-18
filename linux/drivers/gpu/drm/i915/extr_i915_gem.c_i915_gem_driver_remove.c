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
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  uc; int /*<<< orphan*/  awake; } ;
struct TYPE_5__ {int /*<<< orphan*/  userfault_wakeref; } ;
struct drm_i915_private {TYPE_3__ drm; TYPE_1__ gt; TYPE_2__ ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_drain_workqueue (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_suspend_late (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_disable_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fini_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_wakeref_auto_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void i915_gem_driver_remove(struct drm_i915_private *dev_priv)
{
	GEM_BUG_ON(dev_priv->gt.awake);

	intel_wakeref_auto_fini(&dev_priv->ggtt.userfault_wakeref);

	i915_gem_suspend_late(dev_priv);
	intel_disable_gt_powersave(dev_priv);

	/* Flush any outstanding unpin_work. */
	i915_gem_drain_workqueue(dev_priv);

	mutex_lock(&dev_priv->drm.struct_mutex);
	intel_uc_fini_hw(&dev_priv->gt.uc);
	intel_uc_fini(&dev_priv->gt.uc);
	mutex_unlock(&dev_priv->drm.struct_mutex);

	i915_gem_drain_freed_objects(dev_priv);
}