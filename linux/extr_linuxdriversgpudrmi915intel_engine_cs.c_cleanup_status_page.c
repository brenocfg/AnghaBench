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
struct TYPE_2__ {int /*<<< orphan*/  vma; } ;
struct intel_engine_cs {TYPE_1__ status_page; } ;
struct i915_vma {struct drm_i915_gem_object* obj; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_gem_object_release_unless_active (struct drm_i915_gem_object*) ; 
 struct i915_vma* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_vma_close (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 

__attribute__((used)) static void cleanup_status_page(struct intel_engine_cs *engine)
{
	struct i915_vma *vma;
	struct drm_i915_gem_object *obj;

	vma = fetch_and_zero(&engine->status_page.vma);
	if (!vma)
		return;

	obj = vma->obj;

	i915_vma_unpin(vma);
	i915_vma_close(vma);

	i915_gem_object_unpin_map(obj);
	__i915_gem_object_release_unless_active(obj);
}