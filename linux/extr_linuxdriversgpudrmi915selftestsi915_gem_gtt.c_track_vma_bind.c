#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i915_vma {TYPE_2__* vm; int /*<<< orphan*/  vm_link; int /*<<< orphan*/  pages; struct drm_i915_gem_object* obj; } ;
struct TYPE_3__ {int /*<<< orphan*/  pages; } ;
struct drm_i915_gem_object {TYPE_1__ mm; int /*<<< orphan*/  bind_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  inactive_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void track_vma_bind(struct i915_vma *vma)
{
	struct drm_i915_gem_object *obj = vma->obj;

	obj->bind_count++; /* track for eviction later */
	__i915_gem_object_pin_pages(obj);

	vma->pages = obj->mm.pages;
	list_move_tail(&vma->vm_link, &vma->vm->inactive_list);
}