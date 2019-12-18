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
struct i915_vma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 unsigned int __EXEC_OBJECT_HAS_FENCE ; 
 unsigned int __EXEC_OBJECT_HAS_PIN ; 
 int /*<<< orphan*/  __i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  __i915_vma_unpin_fence (struct i915_vma*) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static inline void __eb_unreserve_vma(struct i915_vma *vma, unsigned int flags)
{
	GEM_BUG_ON(!(flags & __EXEC_OBJECT_HAS_PIN));

	if (unlikely(flags & __EXEC_OBJECT_HAS_FENCE))
		__i915_vma_unpin_fence(vma);

	__i915_vma_unpin(vma);
}