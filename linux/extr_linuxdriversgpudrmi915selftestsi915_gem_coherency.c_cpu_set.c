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
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 unsigned int CLFLUSH_AFTER ; 
 unsigned int CLFLUSH_BEFORE ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  clflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_obj_finish_shmem_access (struct drm_i915_gem_object*) ; 
 int i915_gem_obj_prepare_shmem_write (struct drm_i915_gem_object*,unsigned int*) ; 
 struct page* i915_gem_object_get_page (struct drm_i915_gem_object*,unsigned long) ; 
 int /*<<< orphan*/ * kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int offset_in_page (unsigned long) ; 

__attribute__((used)) static int cpu_set(struct drm_i915_gem_object *obj,
		   unsigned long offset,
		   u32 v)
{
	unsigned int needs_clflush;
	struct page *page;
	u32 *map;
	int err;

	err = i915_gem_obj_prepare_shmem_write(obj, &needs_clflush);
	if (err)
		return err;

	page = i915_gem_object_get_page(obj, offset >> PAGE_SHIFT);
	map = kmap_atomic(page);

	if (needs_clflush & CLFLUSH_BEFORE) {
		mb();
		clflush(map+offset_in_page(offset) / sizeof(*map));
		mb();
	}

	map[offset_in_page(offset) / sizeof(*map)] = v;

	if (needs_clflush & CLFLUSH_AFTER) {
		mb();
		clflush(map+offset_in_page(offset) / sizeof(*map));
		mb();
	}

	kunmap_atomic(map);

	i915_gem_obj_finish_shmem_access(obj);
	return 0;
}