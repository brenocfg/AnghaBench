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
struct TYPE_3__ {int /*<<< orphan*/  i915; } ;
struct i915_hw_ppgtt {TYPE_1__ vm; int /*<<< orphan*/  pd_dirty_rings; } ;
struct TYPE_4__ {int /*<<< orphan*/  ring_mask; } ;

/* Variables and functions */
 TYPE_2__* INTEL_INFO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_tlbs_dirty(struct i915_hw_ppgtt *ppgtt)
{
	ppgtt->pd_dirty_rings = INTEL_INFO(ppgtt->vm.i915)->ring_mask;
}