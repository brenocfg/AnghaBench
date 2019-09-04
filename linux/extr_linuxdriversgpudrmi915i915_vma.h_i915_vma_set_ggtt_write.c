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
struct i915_vma {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_VMA_GGTT_WRITE ; 
 int /*<<< orphan*/  i915_vma_is_ggtt (struct i915_vma*) ; 

__attribute__((used)) static inline void i915_vma_set_ggtt_write(struct i915_vma *vma)
{
	GEM_BUG_ON(!i915_vma_is_ggtt(vma));
	vma->flags |= I915_VMA_GGTT_WRITE;
}