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
typedef  int u64 ;
struct TYPE_3__ {int start; } ;
struct i915_vma {unsigned int* exec_flags; scalar_t__ fence; TYPE_1__ node; } ;
struct i915_execbuffer {TYPE_2__* args; } ;
struct drm_i915_gem_exec_object2 {int offset; int /*<<< orphan*/  alignment; int /*<<< orphan*/  pad_to_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BATCH_OFFSET_BIAS ; 
 unsigned int EXEC_OBJECT_NEEDS_FENCE ; 
 unsigned int EXEC_OBJECT_NEEDS_GTT ; 
 unsigned int EXEC_OBJECT_PINNED ; 
 unsigned int EXEC_OBJECT_SUPPORTS_48B_ADDRESS ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int PIN_GLOBAL ; 
 int PIN_MAPPABLE ; 
 int PIN_NONBLOCK ; 
 int PIN_OFFSET_BIAS ; 
 int PIN_OFFSET_FIXED ; 
 int PIN_USER ; 
 int PIN_ZONE_4G ; 
 int UPDATE ; 
 int /*<<< orphan*/  __EXEC_HAS_RELOC ; 
 unsigned int __EXEC_OBJECT_HAS_FENCE ; 
 unsigned int __EXEC_OBJECT_HAS_PIN ; 
 unsigned int __EXEC_OBJECT_NEEDS_BIAS ; 
 unsigned int __EXEC_OBJECT_NEEDS_MAP ; 
 int /*<<< orphan*/  eb_vma_misplaced (struct drm_i915_gem_exec_object2*,struct i915_vma*,unsigned int) ; 
 struct drm_i915_gem_exec_object2* exec_entry (struct i915_execbuffer const*,struct i915_vma*) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i915_vma_pin_fence (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int eb_reserve_vma(const struct i915_execbuffer *eb,
			  struct i915_vma *vma)
{
	struct drm_i915_gem_exec_object2 *entry = exec_entry(eb, vma);
	unsigned int exec_flags = *vma->exec_flags;
	u64 pin_flags;
	int err;

	pin_flags = PIN_USER | PIN_NONBLOCK;
	if (exec_flags & EXEC_OBJECT_NEEDS_GTT)
		pin_flags |= PIN_GLOBAL;

	/*
	 * Wa32bitGeneralStateOffset & Wa32bitInstructionBaseOffset,
	 * limit address to the first 4GBs for unflagged objects.
	 */
	if (!(exec_flags & EXEC_OBJECT_SUPPORTS_48B_ADDRESS))
		pin_flags |= PIN_ZONE_4G;

	if (exec_flags & __EXEC_OBJECT_NEEDS_MAP)
		pin_flags |= PIN_MAPPABLE;

	if (exec_flags & EXEC_OBJECT_PINNED) {
		pin_flags |= entry->offset | PIN_OFFSET_FIXED;
		pin_flags &= ~PIN_NONBLOCK; /* force overlapping checks */
	} else if (exec_flags & __EXEC_OBJECT_NEEDS_BIAS) {
		pin_flags |= BATCH_OFFSET_BIAS | PIN_OFFSET_BIAS;
	}

	err = i915_vma_pin(vma,
			   entry->pad_to_size, entry->alignment,
			   pin_flags);
	if (err)
		return err;

	if (entry->offset != vma->node.start) {
		entry->offset = vma->node.start | UPDATE;
		eb->args->flags |= __EXEC_HAS_RELOC;
	}

	if (unlikely(exec_flags & EXEC_OBJECT_NEEDS_FENCE)) {
		err = i915_vma_pin_fence(vma);
		if (unlikely(err)) {
			i915_vma_unpin(vma);
			return err;
		}

		if (vma->fence)
			exec_flags |= __EXEC_OBJECT_HAS_FENCE;
	}

	*vma->exec_flags = exec_flags | __EXEC_OBJECT_HAS_PIN;
	GEM_BUG_ON(eb_vma_misplaced(entry, vma, exec_flags));

	return 0;
}