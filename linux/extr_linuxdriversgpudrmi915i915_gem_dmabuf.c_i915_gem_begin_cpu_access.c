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
struct TYPE_2__ {struct drm_device* dev; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct dma_buf {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_BIDIRECTIONAL ; 
 int DMA_TO_DEVICE ; 
 struct drm_i915_gem_object* dma_buf_to_obj (struct dma_buf*) ; 
 int i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int i915_gem_object_set_to_cpu_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_gem_begin_cpu_access(struct dma_buf *dma_buf, enum dma_data_direction direction)
{
	struct drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	struct drm_device *dev = obj->base.dev;
	bool write = (direction == DMA_BIDIRECTIONAL || direction == DMA_TO_DEVICE);
	int err;

	err = i915_gem_object_pin_pages(obj);
	if (err)
		return err;

	err = i915_mutex_lock_interruptible(dev);
	if (err)
		goto out;

	err = i915_gem_object_set_to_cpu_domain(obj, write);
	mutex_unlock(&dev->struct_mutex);

out:
	i915_gem_object_unpin_pages(obj);
	return err;
}