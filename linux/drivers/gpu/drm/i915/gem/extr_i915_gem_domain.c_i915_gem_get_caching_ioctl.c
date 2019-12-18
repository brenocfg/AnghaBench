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
struct drm_i915_gem_object {int cache_level; } ;
struct drm_i915_gem_caching {int /*<<< orphan*/  caching; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
#define  I915_CACHE_L3_LLC 130 
#define  I915_CACHE_LLC 129 
#define  I915_CACHE_WT 128 
 int /*<<< orphan*/  I915_CACHING_CACHED ; 
 int /*<<< orphan*/  I915_CACHING_DISPLAY ; 
 int /*<<< orphan*/  I915_CACHING_NONE ; 
 struct drm_i915_gem_object* i915_gem_object_lookup_rcu (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int i915_gem_get_caching_ioctl(struct drm_device *dev, void *data,
			       struct drm_file *file)
{
	struct drm_i915_gem_caching *args = data;
	struct drm_i915_gem_object *obj;
	int err = 0;

	rcu_read_lock();
	obj = i915_gem_object_lookup_rcu(file, args->handle);
	if (!obj) {
		err = -ENOENT;
		goto out;
	}

	switch (obj->cache_level) {
	case I915_CACHE_LLC:
	case I915_CACHE_L3_LLC:
		args->caching = I915_CACHING_CACHED;
		break;

	case I915_CACHE_WT:
		args->caching = I915_CACHING_DISPLAY;
		break;

	default:
		args->caching = I915_CACHING_NONE;
		break;
	}
out:
	rcu_read_unlock();
	return err;
}