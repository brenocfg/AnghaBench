#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int dummy; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; struct sg_table* work; TYPE_2__* mm; } ;
struct TYPE_5__ {int size; } ;
struct drm_i915_gem_object {TYPE_3__ userptr; TYPE_1__ base; } ;
struct TYPE_8__ {struct mm_struct* mm; } ;
struct TYPE_6__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct sg_table* ERR_PTR (int) ; 
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct sg_table*) ; 
 int PTR_ERR_OR_ZERO (struct sg_table*) ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int __get_user_pages_fast (int /*<<< orphan*/ ,int const,int,struct page**) ; 
 struct sg_table* __i915_gem_userptr_alloc_pages (struct drm_i915_gem_object*,struct page**,int const) ; 
 struct sg_table* __i915_gem_userptr_get_pages_schedule (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  __i915_gem_userptr_set_active (struct drm_i915_gem_object*,int) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  i915_gem_object_is_readonly (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 
 struct page** kvmalloc_array (int const,int,int) ; 
 int /*<<< orphan*/  release_pages (struct page**,int) ; 

__attribute__((used)) static int i915_gem_userptr_get_pages(struct drm_i915_gem_object *obj)
{
	const int num_pages = obj->base.size >> PAGE_SHIFT;
	struct mm_struct *mm = obj->userptr.mm->mm;
	struct page **pvec;
	struct sg_table *pages;
	bool active;
	int pinned;

	/* If userspace should engineer that these pages are replaced in
	 * the vma between us binding this page into the GTT and completion
	 * of rendering... Their loss. If they change the mapping of their
	 * pages they need to create a new bo to point to the new vma.
	 *
	 * However, that still leaves open the possibility of the vma
	 * being copied upon fork. Which falls under the same userspace
	 * synchronisation issue as a regular bo, except that this time
	 * the process may not be expecting that a particular piece of
	 * memory is tied to the GPU.
	 *
	 * Fortunately, we can hook into the mmu_notifier in order to
	 * discard the page references prior to anything nasty happening
	 * to the vma (discard or cloning) which should prevent the more
	 * egregious cases from causing harm.
	 */

	if (obj->userptr.work) {
		/* active flag should still be held for the pending work */
		if (IS_ERR(obj->userptr.work))
			return PTR_ERR(obj->userptr.work);
		else
			return -EAGAIN;
	}

	pvec = NULL;
	pinned = 0;

	if (mm == current->mm) {
		pvec = kvmalloc_array(num_pages, sizeof(struct page *),
				      GFP_KERNEL |
				      __GFP_NORETRY |
				      __GFP_NOWARN);
		if (pvec) /* defer to worker if malloc fails */
			pinned = __get_user_pages_fast(obj->userptr.ptr,
						       num_pages,
						       !i915_gem_object_is_readonly(obj),
						       pvec);
	}

	active = false;
	if (pinned < 0) {
		pages = ERR_PTR(pinned);
		pinned = 0;
	} else if (pinned < num_pages) {
		pages = __i915_gem_userptr_get_pages_schedule(obj);
		active = pages == ERR_PTR(-EAGAIN);
	} else {
		pages = __i915_gem_userptr_alloc_pages(obj, pvec, num_pages);
		active = !IS_ERR(pages);
	}
	if (active)
		__i915_gem_userptr_set_active(obj, true);

	if (IS_ERR(pages))
		release_pages(pvec, pinned);
	kvfree(pvec);

	return PTR_ERR_OR_ZERO(pages);
}