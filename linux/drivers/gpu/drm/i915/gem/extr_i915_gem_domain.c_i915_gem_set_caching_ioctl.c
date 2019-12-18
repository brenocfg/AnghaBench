#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct drm_i915_gem_object {int cache_level; } ;
struct drm_i915_gem_caching {int caching; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  HAS_LLC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_SNOOP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_WT (struct drm_i915_private*) ; 
 int I915_CACHE_LLC ; 
 int I915_CACHE_NONE ; 
 int I915_CACHE_WT ; 
#define  I915_CACHING_CACHED 130 
#define  I915_CACHING_DISPLAY 129 
#define  I915_CACHING_NONE 128 
 int /*<<< orphan*/  I915_WAIT_INTERRUPTIBLE ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 scalar_t__ i915_gem_object_is_proxy (struct drm_i915_gem_object*) ; 
 int i915_gem_object_lock_interruptible (struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* i915_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int i915_gem_object_set_cache_level (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int i915_gem_object_wait (struct drm_i915_gem_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

int i915_gem_set_caching_ioctl(struct drm_device *dev, void *data,
			       struct drm_file *file)
{
	struct drm_i915_private *i915 = to_i915(dev);
	struct drm_i915_gem_caching *args = data;
	struct drm_i915_gem_object *obj;
	enum i915_cache_level level;
	int ret = 0;

	switch (args->caching) {
	case I915_CACHING_NONE:
		level = I915_CACHE_NONE;
		break;
	case I915_CACHING_CACHED:
		/*
		 * Due to a HW issue on BXT A stepping, GPU stores via a
		 * snooped mapping may leave stale data in a corresponding CPU
		 * cacheline, whereas normally such cachelines would get
		 * invalidated.
		 */
		if (!HAS_LLC(i915) && !HAS_SNOOP(i915))
			return -ENODEV;

		level = I915_CACHE_LLC;
		break;
	case I915_CACHING_DISPLAY:
		level = HAS_WT(i915) ? I915_CACHE_WT : I915_CACHE_NONE;
		break;
	default:
		return -EINVAL;
	}

	obj = i915_gem_object_lookup(file, args->handle);
	if (!obj)
		return -ENOENT;

	/*
	 * The caching mode of proxy object is handled by its generator, and
	 * not allowed to be changed by userspace.
	 */
	if (i915_gem_object_is_proxy(obj)) {
		ret = -ENXIO;
		goto out;
	}

	if (obj->cache_level == level)
		goto out;

	ret = i915_gem_object_wait(obj,
				   I915_WAIT_INTERRUPTIBLE,
				   MAX_SCHEDULE_TIMEOUT);
	if (ret)
		goto out;

	ret = mutex_lock_interruptible(&i915->drm.struct_mutex);
	if (ret)
		goto out;

	ret = i915_gem_object_lock_interruptible(obj);
	if (ret == 0) {
		ret = i915_gem_object_set_cache_level(obj, level);
		i915_gem_object_unlock(obj);
	}
	mutex_unlock(&i915->drm.struct_mutex);

out:
	i915_gem_object_put(obj);
	return ret;
}