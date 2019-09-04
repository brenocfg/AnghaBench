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
typedef  unsigned int u32 ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 unsigned int CLFLUSH_BEFORE ; 
 unsigned int DW_PER_PAGE ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int STACK_MAGIC ; 
 int /*<<< orphan*/  drm_clflush_virt_range (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_obj_finish_shmem_access (struct drm_i915_gem_object*) ; 
 int i915_gem_obj_prepare_shmem_read (struct drm_i915_gem_object*,unsigned int*) ; 
 int /*<<< orphan*/  i915_gem_object_get_page (struct drm_i915_gem_object*,unsigned int) ; 
 unsigned int* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned int*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int real_page_count (struct drm_i915_gem_object*) ; 

__attribute__((used)) static int cpu_check(struct drm_i915_gem_object *obj, unsigned int max)
{
	unsigned int n, m, needs_flush;
	int err;

	err = i915_gem_obj_prepare_shmem_read(obj, &needs_flush);
	if (err)
		return err;

	for (n = 0; n < real_page_count(obj); n++) {
		u32 *map;

		map = kmap_atomic(i915_gem_object_get_page(obj, n));
		if (needs_flush & CLFLUSH_BEFORE)
			drm_clflush_virt_range(map, PAGE_SIZE);

		for (m = 0; m < max; m++) {
			if (map[m] != m) {
				pr_err("Invalid value at page %d, offset %d: found %x expected %x\n",
				       n, m, map[m], m);
				err = -EINVAL;
				goto out_unmap;
			}
		}

		for (; m < DW_PER_PAGE; m++) {
			if (map[m] != STACK_MAGIC) {
				pr_err("Invalid value at page %d, offset %d: found %x expected %x\n",
				       n, m, map[m], STACK_MAGIC);
				err = -EINVAL;
				goto out_unmap;
			}
		}

out_unmap:
		kunmap_atomic(map);
		if (err)
			break;
	}

	i915_gem_obj_finish_shmem_access(obj);
	return err;
}