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
struct drm_i915_gem_object {int /*<<< orphan*/  cache_dirty; } ;
struct clflush {int /*<<< orphan*/  obj; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clflush_ops ; 
 int /*<<< orphan*/  dma_fence_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_get (struct drm_i915_gem_object*) ; 
 struct clflush* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clflush *clflush_work_create(struct drm_i915_gem_object *obj)
{
	struct clflush *clflush;

	GEM_BUG_ON(!obj->cache_dirty);

	clflush = kmalloc(sizeof(*clflush), GFP_KERNEL);
	if (!clflush)
		return NULL;

	dma_fence_work_init(&clflush->base, &clflush_ops);
	clflush->obj = i915_gem_object_get(obj); /* obj <-> clflush cycle */

	return clflush;
}