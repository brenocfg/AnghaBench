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
struct TYPE_2__ {int size; int start; } ;
struct i915_vma {TYPE_1__ node; } ;
struct drm_i915_gem_exec_object2 {int pad_to_size; int offset; scalar_t__ alignment; } ;

/* Variables and functions */
 int BATCH_OFFSET_BIAS ; 
 unsigned int EXEC_OBJECT_PINNED ; 
 unsigned int EXEC_OBJECT_SUPPORTS_48B_ADDRESS ; 
 int /*<<< orphan*/  IS_ALIGNED (int,scalar_t__) ; 
 unsigned int __EXEC_OBJECT_NEEDS_BIAS ; 
 unsigned int __EXEC_OBJECT_NEEDS_MAP ; 
 int /*<<< orphan*/  i915_vma_is_map_and_fenceable (struct i915_vma const*) ; 

__attribute__((used)) static bool
eb_vma_misplaced(const struct drm_i915_gem_exec_object2 *entry,
		 const struct i915_vma *vma,
		 unsigned int flags)
{
	if (vma->node.size < entry->pad_to_size)
		return true;

	if (entry->alignment && !IS_ALIGNED(vma->node.start, entry->alignment))
		return true;

	if (flags & EXEC_OBJECT_PINNED &&
	    vma->node.start != entry->offset)
		return true;

	if (flags & __EXEC_OBJECT_NEEDS_BIAS &&
	    vma->node.start < BATCH_OFFSET_BIAS)
		return true;

	if (!(flags & EXEC_OBJECT_SUPPORTS_48B_ADDRESS) &&
	    (vma->node.start + vma->node.size - 1) >> 32)
		return true;

	if (flags & __EXEC_OBJECT_NEEDS_MAP &&
	    !i915_vma_is_map_and_fenceable(vma))
		return true;

	return false;
}