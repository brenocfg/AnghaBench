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
struct i915_vma {TYPE_1__* fence; } ;
struct TYPE_2__ {scalar_t__ pin_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 

__attribute__((used)) static inline void __i915_vma_unpin_fence(struct i915_vma *vma)
{
	GEM_BUG_ON(vma->fence->pin_count <= 0);
	vma->fence->pin_count--;
}