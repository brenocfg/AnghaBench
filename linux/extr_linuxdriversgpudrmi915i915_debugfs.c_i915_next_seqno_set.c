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
typedef  int /*<<< orphan*/  u64 ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {struct drm_device drm; } ;

/* Variables and functions */
 int i915_gem_set_global_seqno (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i915_next_seqno_set(void *data, u64 val)
{
	struct drm_i915_private *dev_priv = data;
	struct drm_device *dev = &dev_priv->drm;
	int ret;

	ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		return ret;

	intel_runtime_pm_get(dev_priv);
	ret = i915_gem_set_global_seqno(dev, val);
	intel_runtime_pm_put(dev_priv);

	mutex_unlock(&dev->struct_mutex);

	return ret;
}