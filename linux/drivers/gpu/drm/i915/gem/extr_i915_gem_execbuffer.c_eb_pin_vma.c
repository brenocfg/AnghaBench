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
typedef  int u64 ;
struct TYPE_2__ {int start; scalar_t__ size; } ;
struct i915_vma {unsigned int* exec_flags; scalar_t__ fence; TYPE_1__ node; } ;
struct i915_execbuffer {int dummy; } ;
struct drm_i915_gem_exec_object2 {int offset; } ;

/* Variables and functions */
 unsigned int EXEC_OBJECT_NEEDS_FENCE ; 
 unsigned int EXEC_OBJECT_NEEDS_GTT ; 
 int PIN_GLOBAL ; 
 int PIN_NOEVICT ; 
 int PIN_OFFSET_FIXED ; 
 int PIN_OFFSET_MASK ; 
 int PIN_USER ; 
 unsigned int __EXEC_OBJECT_HAS_FENCE ; 
 unsigned int __EXEC_OBJECT_HAS_PIN ; 
 int /*<<< orphan*/  eb_vma_misplaced (struct drm_i915_gem_exec_object2 const*,struct i915_vma*,unsigned int) ; 
 unsigned int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int i915_vma_pin_fence (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static inline bool
eb_pin_vma(struct i915_execbuffer *eb,
	   const struct drm_i915_gem_exec_object2 *entry,
	   struct i915_vma *vma)
{
	unsigned int exec_flags = *vma->exec_flags;
	u64 pin_flags;

	if (vma->node.size)
		pin_flags = vma->node.start;
	else
		pin_flags = entry->offset & PIN_OFFSET_MASK;

	pin_flags |= PIN_USER | PIN_NOEVICT | PIN_OFFSET_FIXED;
	if (unlikely(exec_flags & EXEC_OBJECT_NEEDS_GTT))
		pin_flags |= PIN_GLOBAL;

	if (unlikely(i915_vma_pin(vma, 0, 0, pin_flags)))
		return false;

	if (unlikely(exec_flags & EXEC_OBJECT_NEEDS_FENCE)) {
		if (unlikely(i915_vma_pin_fence(vma))) {
			i915_vma_unpin(vma);
			return false;
		}

		if (vma->fence)
			exec_flags |= __EXEC_OBJECT_HAS_FENCE;
	}

	*vma->exec_flags = exec_flags | __EXEC_OBJECT_HAS_PIN;
	return !eb_vma_misplaced(entry, vma, exec_flags);
}