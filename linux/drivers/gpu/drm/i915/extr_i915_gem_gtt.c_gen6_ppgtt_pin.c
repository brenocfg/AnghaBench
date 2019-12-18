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
struct i915_ppgtt {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  closed; } ;
struct TYPE_4__ {TYPE_1__ vm; } ;
struct gen6_ppgtt {scalar_t__ pin_count; int /*<<< orphan*/  vma; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN6_PD_ALIGN ; 
 int PIN_GLOBAL ; 
 int PIN_HIGH ; 
 int i915_vma_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct gen6_ppgtt* to_gen6_ppgtt (struct i915_ppgtt*) ; 

int gen6_ppgtt_pin(struct i915_ppgtt *base)
{
	struct gen6_ppgtt *ppgtt = to_gen6_ppgtt(base);
	int err;

	GEM_BUG_ON(ppgtt->base.vm.closed);

	/*
	 * Workaround the limited maximum vma->pin_count and the aliasing_ppgtt
	 * which will be pinned into every active context.
	 * (When vma->pin_count becomes atomic, I expect we will naturally
	 * need a larger, unpacked, type and kill this redundancy.)
	 */
	if (ppgtt->pin_count++)
		return 0;

	/*
	 * PPGTT PDEs reside in the GGTT and consists of 512 entries. The
	 * allocator works in address space sizes, so it's multiplied by page
	 * size. We allocate at the top of the GTT to avoid fragmentation.
	 */
	err = i915_vma_pin(ppgtt->vma,
			   0, GEN6_PD_ALIGN,
			   PIN_GLOBAL | PIN_HIGH);
	if (err)
		goto unpin;

	return 0;

unpin:
	ppgtt->pin_count = 0;
	return err;
}