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
struct i915_vma {int exec_flags; int /*<<< orphan*/  obj; } ;
struct TYPE_2__ {scalar_t__ needs_unfenced; int /*<<< orphan*/  has_fence; } ;
struct i915_execbuffer {int invalid_flags; int context_flags; TYPE_1__ reloc_cache; struct drm_i915_gem_exec_object2* exec; } ;
struct drm_i915_gem_exec_object2 {int flags; int offset; int /*<<< orphan*/  handle; scalar_t__ pad_to_size; scalar_t__ alignment; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int EXEC_OBJECT_NEEDS_FENCE ; 
 int EXEC_OBJECT_NEEDS_GTT ; 
 int EXEC_OBJECT_PAD_TO_SIZE ; 
 int EXEC_OBJECT_PINNED ; 
 int I915_GTT_PAGE_MASK ; 
 int __EXEC_OBJECT_NEEDS_MAP ; 
 int gen8_canonical_addr (int) ; 
 int gen8_noncanonical_addr (int) ; 
 scalar_t__ i915_gem_object_is_tiled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 int offset_in_page (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
eb_validate_vma(struct i915_execbuffer *eb,
		struct drm_i915_gem_exec_object2 *entry,
		struct i915_vma *vma)
{
	if (unlikely(entry->flags & eb->invalid_flags))
		return -EINVAL;

	if (unlikely(entry->alignment && !is_power_of_2(entry->alignment)))
		return -EINVAL;

	/*
	 * Offset can be used as input (EXEC_OBJECT_PINNED), reject
	 * any non-page-aligned or non-canonical addresses.
	 */
	if (unlikely(entry->flags & EXEC_OBJECT_PINNED &&
		     entry->offset != gen8_canonical_addr(entry->offset & I915_GTT_PAGE_MASK)))
		return -EINVAL;

	/* pad_to_size was once a reserved field, so sanitize it */
	if (entry->flags & EXEC_OBJECT_PAD_TO_SIZE) {
		if (unlikely(offset_in_page(entry->pad_to_size)))
			return -EINVAL;
	} else {
		entry->pad_to_size = 0;
	}

	if (unlikely(vma->exec_flags)) {
		DRM_DEBUG("Object [handle %d, index %d] appears more than once in object list\n",
			  entry->handle, (int)(entry - eb->exec));
		return -EINVAL;
	}

	/*
	 * From drm_mm perspective address space is continuous,
	 * so from this point we're always using non-canonical
	 * form internally.
	 */
	entry->offset = gen8_noncanonical_addr(entry->offset);

	if (!eb->reloc_cache.has_fence) {
		entry->flags &= ~EXEC_OBJECT_NEEDS_FENCE;
	} else {
		if ((entry->flags & EXEC_OBJECT_NEEDS_FENCE ||
		     eb->reloc_cache.needs_unfenced) &&
		    i915_gem_object_is_tiled(vma->obj))
			entry->flags |= EXEC_OBJECT_NEEDS_GTT | __EXEC_OBJECT_NEEDS_MAP;
	}

	if (!(entry->flags & EXEC_OBJECT_PINNED))
		entry->flags |= eb->context_flags;

	return 0;
}