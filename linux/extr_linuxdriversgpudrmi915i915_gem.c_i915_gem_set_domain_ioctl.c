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
typedef  int uint32_t ;
struct drm_i915_gem_set_domain {int read_domains; int write_domain; int /*<<< orphan*/  handle; } ;
struct drm_i915_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int I915_GEM_DOMAIN_GTT ; 
 int I915_GEM_DOMAIN_WC ; 
 int I915_GEM_GPU_DOMAINS ; 
 int I915_WAIT_ALL ; 
 int I915_WAIT_INTERRUPTIBLE ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  fb_write_origin (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_bump_inactive_ggtt (struct drm_i915_gem_object*) ; 
 scalar_t__ i915_gem_object_is_proxy (struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* i915_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int i915_gem_object_set_to_cpu_domain (struct drm_i915_gem_object*,int) ; 
 int i915_gem_object_set_to_gtt_domain (struct drm_i915_gem_object*,int) ; 
 int i915_gem_object_set_to_wc_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 
 int i915_gem_object_wait (struct drm_i915_gem_object*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  intel_fb_obj_invalidate (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_rps_client (struct drm_file*) ; 

int
i915_gem_set_domain_ioctl(struct drm_device *dev, void *data,
			  struct drm_file *file)
{
	struct drm_i915_gem_set_domain *args = data;
	struct drm_i915_gem_object *obj;
	uint32_t read_domains = args->read_domains;
	uint32_t write_domain = args->write_domain;
	int err;

	/* Only handle setting domains to types used by the CPU. */
	if ((write_domain | read_domains) & I915_GEM_GPU_DOMAINS)
		return -EINVAL;

	/* Having something in the write domain implies it's in the read
	 * domain, and only that read domain.  Enforce that in the request.
	 */
	if (write_domain != 0 && read_domains != write_domain)
		return -EINVAL;

	obj = i915_gem_object_lookup(file, args->handle);
	if (!obj)
		return -ENOENT;

	/* Try to flush the object off the GPU without holding the lock.
	 * We will repeat the flush holding the lock in the normal manner
	 * to catch cases where we are gazumped.
	 */
	err = i915_gem_object_wait(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   (write_domain ? I915_WAIT_ALL : 0),
				   MAX_SCHEDULE_TIMEOUT,
				   to_rps_client(file));
	if (err)
		goto out;

	/*
	 * Proxy objects do not control access to the backing storage, ergo
	 * they cannot be used as a means to manipulate the cache domain
	 * tracking for that backing storage. The proxy object is always
	 * considered to be outside of any cache domain.
	 */
	if (i915_gem_object_is_proxy(obj)) {
		err = -ENXIO;
		goto out;
	}

	/*
	 * Flush and acquire obj->pages so that we are coherent through
	 * direct access in memory with previous cached writes through
	 * shmemfs and that our cache domain tracking remains valid.
	 * For example, if the obj->filp was moved to swap without us
	 * being notified and releasing the pages, we would mistakenly
	 * continue to assume that the obj remained out of the CPU cached
	 * domain.
	 */
	err = i915_gem_object_pin_pages(obj);
	if (err)
		goto out;

	err = i915_mutex_lock_interruptible(dev);
	if (err)
		goto out_unpin;

	if (read_domains & I915_GEM_DOMAIN_WC)
		err = i915_gem_object_set_to_wc_domain(obj, write_domain);
	else if (read_domains & I915_GEM_DOMAIN_GTT)
		err = i915_gem_object_set_to_gtt_domain(obj, write_domain);
	else
		err = i915_gem_object_set_to_cpu_domain(obj, write_domain);

	/* And bump the LRU for this access */
	i915_gem_object_bump_inactive_ggtt(obj);

	mutex_unlock(&dev->struct_mutex);

	if (write_domain != 0)
		intel_fb_obj_invalidate(obj,
					fb_write_origin(obj, write_domain));

out_unpin:
	i915_gem_object_unpin_pages(obj);
out:
	i915_gem_object_put(obj);
	return err;
}