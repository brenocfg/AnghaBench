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
struct i915_ppgtt {int /*<<< orphan*/  pd; } ;
struct i915_address_space {int /*<<< orphan*/  top; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gen8_ppgtt_cleanup (struct i915_address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_scratch (struct i915_address_space*) ; 
 int /*<<< orphan*/  gen8_pd_top_count (struct i915_address_space*) ; 
 int /*<<< orphan*/  gen8_ppgtt_notify_vgt (struct i915_ppgtt*,int) ; 
 struct i915_ppgtt* i915_vm_to_ppgtt (struct i915_address_space*) ; 
 scalar_t__ intel_vgpu_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_ppgtt_cleanup(struct i915_address_space *vm)
{
	struct i915_ppgtt *ppgtt = i915_vm_to_ppgtt(vm);

	if (intel_vgpu_active(vm->i915))
		gen8_ppgtt_notify_vgt(ppgtt, false);

	__gen8_ppgtt_cleanup(vm, ppgtt->pd, gen8_pd_top_count(vm), vm->top);
	free_scratch(vm);
}