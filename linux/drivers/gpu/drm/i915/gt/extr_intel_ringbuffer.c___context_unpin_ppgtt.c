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
struct intel_context {int dummy; } ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen6_ppgtt_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vm_to_ppgtt (struct i915_address_space*) ; 
 struct i915_address_space* vm_alias (struct intel_context*) ; 

__attribute__((used)) static void __context_unpin_ppgtt(struct intel_context *ce)
{
	struct i915_address_space *vm;

	vm = vm_alias(ce);
	if (vm)
		gen6_ppgtt_unpin(i915_vm_to_ppgtt(vm));
}