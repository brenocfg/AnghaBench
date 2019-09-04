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
struct intel_context {struct i915_vma* state; } ;
struct i915_vma {TYPE_1__* obj; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin_global; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 

__attribute__((used)) static void __context_unpin(struct intel_context *ce)
{
	struct i915_vma *vma;

	vma = ce->state;
	if (!vma)
		return;

	vma->obj->pin_global--;
	i915_vma_unpin(vma);
}