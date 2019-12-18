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
typedef  int /*<<< orphan*/  u64 ;
struct i915_vma {int dummy; } ;
struct TYPE_2__ {int probability; int interval; int /*<<< orphan*/  times; } ;
struct i915_address_space {TYPE_1__ fault_attr; } ;
struct drm_i915_private {int dummy; } ;
typedef  struct i915_vma drm_i915_gem_object ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 unsigned int PIN_OFFSET_FIXED ; 
 unsigned int PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 unsigned int SZ_1G ; 
 unsigned int SZ_2M ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cleanup_freed_objects (struct drm_i915_private*) ; 
 struct i915_vma* fake_dma_object (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct i915_vma*,struct i915_address_space*,int /*<<< orphan*/ *) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int shrink_boom(struct drm_i915_private *i915,
		       struct i915_address_space *vm,
		       u64 hole_start, u64 hole_end,
		       unsigned long end_time)
{
	unsigned int sizes[] = { SZ_2M, SZ_1G };
	struct drm_i915_gem_object *purge;
	struct drm_i915_gem_object *explode;
	int err;
	int i;

	/*
	 * Catch the case which shrink_hole seems to miss. The setup here
	 * requires invoking the shrinker as we do the alloc_pt/alloc_pd, while
	 * ensuring that all vma assiocated with the respective pd/pdp are
	 * unpinned at the time.
	 */

	for (i = 0; i < ARRAY_SIZE(sizes); ++i) {
		unsigned int flags = PIN_USER | PIN_OFFSET_FIXED;
		unsigned int size = sizes[i];
		struct i915_vma *vma;

		purge = fake_dma_object(i915, size);
		if (IS_ERR(purge))
			return PTR_ERR(purge);

		vma = i915_vma_instance(purge, vm, NULL);
		if (IS_ERR(vma)) {
			err = PTR_ERR(vma);
			goto err_purge;
		}

		err = i915_vma_pin(vma, 0, 0, flags);
		if (err)
			goto err_purge;

		/* Should now be ripe for purging */
		i915_vma_unpin(vma);

		explode = fake_dma_object(i915, size);
		if (IS_ERR(explode)) {
			err = PTR_ERR(explode);
			goto err_purge;
		}

		vm->fault_attr.probability = 100;
		vm->fault_attr.interval = 1;
		atomic_set(&vm->fault_attr.times, -1);

		vma = i915_vma_instance(explode, vm, NULL);
		if (IS_ERR(vma)) {
			err = PTR_ERR(vma);
			goto err_explode;
		}

		err = i915_vma_pin(vma, 0, 0, flags | size);
		if (err)
			goto err_explode;

		i915_vma_unpin(vma);

		i915_gem_object_put(purge);
		i915_gem_object_put(explode);

		memset(&vm->fault_attr, 0, sizeof(vm->fault_attr));
		cleanup_freed_objects(i915);
	}

	return 0;

err_explode:
	i915_gem_object_put(explode);
err_purge:
	i915_gem_object_put(purge);
	memset(&vm->fault_attr, 0, sizeof(vm->fault_attr));
	return err;
}