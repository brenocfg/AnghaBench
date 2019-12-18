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
struct drm_i915_gem_object {int dummy; } ;
struct dma_buf {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 struct drm_i915_gem_object* dma_buf_to_obj (struct dma_buf*) ; 
 int i915_gem_object_lock_interruptible (struct drm_i915_gem_object*) ; 
 int i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int i915_gem_object_set_to_gtt_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 

__attribute__((used)) static int i915_gem_end_cpu_access(struct dma_buf *dma_buf, enum dma_data_direction direction)
{
	struct drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	int err;

	err = i915_gem_object_pin_pages(obj);
	if (err)
		return err;

	err = i915_gem_object_lock_interruptible(obj);
	if (err)
		goto out;

	err = i915_gem_object_set_to_gtt_domain(obj, false);
	i915_gem_object_unlock(obj);

out:
	i915_gem_object_unpin_pages(obj);
	return err;
}