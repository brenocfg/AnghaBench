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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  vma_node; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  drm_vma_node_offset_addr (int /*<<< orphan*/ *) ; 
 int i915_gem_object_create_mmap_offset (struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* i915_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 

int
i915_gem_mmap_gtt(struct drm_file *file,
		  struct drm_device *dev,
		  uint32_t handle,
		  uint64_t *offset)
{
	struct drm_i915_gem_object *obj;
	int ret;

	obj = i915_gem_object_lookup(file, handle);
	if (!obj)
		return -ENOENT;

	ret = i915_gem_object_create_mmap_offset(obj);
	if (ret == 0)
		*offset = drm_vma_node_offset_addr(&obj->base.vma_node);

	i915_gem_object_put(obj);
	return ret;
}