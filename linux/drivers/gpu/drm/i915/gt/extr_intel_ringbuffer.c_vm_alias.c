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
struct intel_context {struct i915_address_space* vm; } ;
struct i915_address_space {int dummy; } ;
struct TYPE_4__ {TYPE_1__* alias; } ;
struct TYPE_3__ {struct i915_address_space vm; } ;

/* Variables and functions */
 scalar_t__ i915_is_ggtt (struct i915_address_space*) ; 
 TYPE_2__* i915_vm_to_ggtt (struct i915_address_space*) ; 

__attribute__((used)) static struct i915_address_space *vm_alias(struct intel_context *ce)
{
	struct i915_address_space *vm;

	vm = ce->vm;
	if (i915_is_ggtt(vm))
		vm = &i915_vm_to_ggtt(vm)->alias->vm;

	return vm;
}