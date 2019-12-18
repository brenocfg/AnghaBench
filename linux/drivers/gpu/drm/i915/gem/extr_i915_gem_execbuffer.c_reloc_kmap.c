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
struct TYPE_2__ {void* mm; } ;
struct reloc_cache {long vaddr; unsigned long page; TYPE_1__ node; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (unsigned int) ; 
 unsigned int CLFLUSH_FLAGS ; 
 void* ERR_PTR (int) ; 
 unsigned int KMAP ; 
 unsigned int PAGE_MASK ; 
 int /*<<< orphan*/  i915_gem_object_get_dirty_page (struct drm_i915_gem_object*,unsigned long) ; 
 int i915_gem_object_prepare_write (struct drm_i915_gem_object*,unsigned int*) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 unsigned long unmask_flags (unsigned long) ; 
 int /*<<< orphan*/  unmask_page (long) ; 

__attribute__((used)) static void *reloc_kmap(struct drm_i915_gem_object *obj,
			struct reloc_cache *cache,
			unsigned long page)
{
	void *vaddr;

	if (cache->vaddr) {
		kunmap_atomic(unmask_page(cache->vaddr));
	} else {
		unsigned int flushes;
		int err;

		err = i915_gem_object_prepare_write(obj, &flushes);
		if (err)
			return ERR_PTR(err);

		BUILD_BUG_ON(KMAP & CLFLUSH_FLAGS);
		BUILD_BUG_ON((KMAP | CLFLUSH_FLAGS) & PAGE_MASK);

		cache->vaddr = flushes | KMAP;
		cache->node.mm = (void *)obj;
		if (flushes)
			mb();
	}

	vaddr = kmap_atomic(i915_gem_object_get_dirty_page(obj, page));
	cache->vaddr = unmask_flags(cache->vaddr) | (unsigned long)vaddr;
	cache->page = page;

	return vaddr;
}