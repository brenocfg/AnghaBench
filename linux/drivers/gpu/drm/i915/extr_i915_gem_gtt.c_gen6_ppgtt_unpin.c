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
struct i915_ppgtt {int dummy; } ;
struct gen6_ppgtt {int /*<<< orphan*/  vma; scalar_t__ pin_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_vma_unpin (int /*<<< orphan*/ ) ; 
 struct gen6_ppgtt* to_gen6_ppgtt (struct i915_ppgtt*) ; 

void gen6_ppgtt_unpin(struct i915_ppgtt *base)
{
	struct gen6_ppgtt *ppgtt = to_gen6_ppgtt(base);

	GEM_BUG_ON(!ppgtt->pin_count);
	if (--ppgtt->pin_count)
		return;

	i915_vma_unpin(ppgtt->vma);
}