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
typedef  scalar_t__ u64 ;
struct i915_address_space {int /*<<< orphan*/  mm; TYPE_4__* i915; } ;
struct drm_mm_node {int dummy; } ;
typedef  enum drm_mm_insert_mode { ____Placeholder_drm_mm_insert_mode } drm_mm_insert_mode ;
struct TYPE_7__ {TYPE_2__* alias; } ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_8__ {TYPE_3__ ggtt; TYPE_1__ drm; } ;
struct TYPE_6__ {struct i915_address_space vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int DRM_MM_INSERT_BEST ; 
 int DRM_MM_INSERT_EVICT ; 
 int DRM_MM_INSERT_HIGHEST ; 
 int DRM_MM_INSERT_LOW ; 
 int DRM_MM_INSERT_ONCE ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ I915_GTT_MIN_ALIGNMENT ; 
 scalar_t__ I915_GTT_PAGE_SIZE ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,scalar_t__) ; 
 unsigned int PIN_HIGH ; 
 unsigned int PIN_MAPPABLE ; 
 unsigned int PIN_NOEVICT ; 
 unsigned int PIN_NOSEARCH ; 
 scalar_t__ U64_MAX ; 
 int drm_mm_insert_node_in_range (int /*<<< orphan*/ *,struct drm_mm_node*,scalar_t__,scalar_t__,unsigned long,scalar_t__,scalar_t__,int) ; 
 int drm_mm_node_allocated (struct drm_mm_node*) ; 
 int i915_gem_evict_something (struct i915_address_space*,scalar_t__,scalar_t__,unsigned long,scalar_t__,scalar_t__,unsigned int) ; 
 int i915_gem_gtt_reserve (struct i915_address_space*,struct drm_mm_node*,scalar_t__,scalar_t__,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ random_offset (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int range_overflows (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ round_down (scalar_t__,scalar_t__) ; 
 scalar_t__ round_up (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int i915_gem_gtt_insert(struct i915_address_space *vm,
			struct drm_mm_node *node,
			u64 size, u64 alignment, unsigned long color,
			u64 start, u64 end, unsigned int flags)
{
	enum drm_mm_insert_mode mode;
	u64 offset;
	int err;

	lockdep_assert_held(&vm->i915->drm.struct_mutex);
	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(alignment && !is_power_of_2(alignment));
	GEM_BUG_ON(alignment && !IS_ALIGNED(alignment, I915_GTT_MIN_ALIGNMENT));
	GEM_BUG_ON(start >= end);
	GEM_BUG_ON(start > 0  && !IS_ALIGNED(start, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(end < U64_MAX && !IS_ALIGNED(end, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(vm == &vm->i915->ggtt.alias->vm);
	GEM_BUG_ON(drm_mm_node_allocated(node));

	if (unlikely(range_overflows(start, size, end)))
		return -ENOSPC;

	if (unlikely(round_up(start, alignment) > round_down(end - size, alignment)))
		return -ENOSPC;

	mode = DRM_MM_INSERT_BEST;
	if (flags & PIN_HIGH)
		mode = DRM_MM_INSERT_HIGHEST;
	if (flags & PIN_MAPPABLE)
		mode = DRM_MM_INSERT_LOW;

	/* We only allocate in PAGE_SIZE/GTT_PAGE_SIZE (4096) chunks,
	 * so we know that we always have a minimum alignment of 4096.
	 * The drm_mm range manager is optimised to return results
	 * with zero alignment, so where possible use the optimal
	 * path.
	 */
	BUILD_BUG_ON(I915_GTT_MIN_ALIGNMENT > I915_GTT_PAGE_SIZE);
	if (alignment <= I915_GTT_MIN_ALIGNMENT)
		alignment = 0;

	err = drm_mm_insert_node_in_range(&vm->mm, node,
					  size, alignment, color,
					  start, end, mode);
	if (err != -ENOSPC)
		return err;

	if (mode & DRM_MM_INSERT_ONCE) {
		err = drm_mm_insert_node_in_range(&vm->mm, node,
						  size, alignment, color,
						  start, end,
						  DRM_MM_INSERT_BEST);
		if (err != -ENOSPC)
			return err;
	}

	if (flags & PIN_NOEVICT)
		return -ENOSPC;

	/*
	 * No free space, pick a slot at random.
	 *
	 * There is a pathological case here using a GTT shared between
	 * mmap and GPU (i.e. ggtt/aliasing_ppgtt but not full-ppgtt):
	 *
	 *    |<-- 256 MiB aperture -->||<-- 1792 MiB unmappable -->|
	 *         (64k objects)             (448k objects)
	 *
	 * Now imagine that the eviction LRU is ordered top-down (just because
	 * pathology meets real life), and that we need to evict an object to
	 * make room inside the aperture. The eviction scan then has to walk
	 * the 448k list before it finds one within range. And now imagine that
	 * it has to search for a new hole between every byte inside the memcpy,
	 * for several simultaneous clients.
	 *
	 * On a full-ppgtt system, if we have run out of available space, there
	 * will be lots and lots of objects in the eviction list! Again,
	 * searching that LRU list may be slow if we are also applying any
	 * range restrictions (e.g. restriction to low 4GiB) and so, for
	 * simplicity and similarilty between different GTT, try the single
	 * random replacement first.
	 */
	offset = random_offset(start, end,
			       size, alignment ?: I915_GTT_MIN_ALIGNMENT);
	err = i915_gem_gtt_reserve(vm, node, size, offset, color, flags);
	if (err != -ENOSPC)
		return err;

	if (flags & PIN_NOSEARCH)
		return -ENOSPC;

	/* Randomly selected placement is pinned, do a search */
	err = i915_gem_evict_something(vm, size, alignment, color,
				       start, end, flags);
	if (err)
		return err;

	return drm_mm_insert_node_in_range(&vm->mm, node,
					   size, alignment, color,
					   start, end, DRM_MM_INSERT_EVICT);
}