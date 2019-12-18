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
struct i915_vma {struct drm_i915_gem_object* obj; } ;
struct i915_request {int dummy; } ;
struct drm_i915_gem_object {int cache_dirty; int cache_coherent; scalar_t__ write_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 int /*<<< orphan*/  i915_gem_clflush_object (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int i915_request_await_object (struct i915_request*,struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_vma_lock (struct i915_vma*) ; 
 int i915_vma_move_to_active (struct i915_vma*,struct i915_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unlock (struct i915_vma*) ; 

__attribute__((used)) static int reloc_move_to_gpu(struct i915_request *rq, struct i915_vma *vma)
{
	struct drm_i915_gem_object *obj = vma->obj;
	int err;

	i915_vma_lock(vma);

	if (obj->cache_dirty & ~obj->cache_coherent)
		i915_gem_clflush_object(obj, 0);
	obj->write_domain = 0;

	err = i915_request_await_object(rq, vma->obj, true);
	if (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);

	i915_vma_unlock(vma);

	return err;
}