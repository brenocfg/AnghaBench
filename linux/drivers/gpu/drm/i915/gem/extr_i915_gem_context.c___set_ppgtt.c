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
struct i915_gem_context {struct i915_address_space* vm; } ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __apply_ppgtt ; 
 int /*<<< orphan*/  context_apply_all (struct i915_gem_context*,int /*<<< orphan*/ ,struct i915_address_space*) ; 
 struct i915_address_space* i915_vm_get (struct i915_address_space*) ; 
 scalar_t__ i915_vm_is_4lvl (struct i915_address_space*) ; 

__attribute__((used)) static struct i915_address_space *
__set_ppgtt(struct i915_gem_context *ctx, struct i915_address_space *vm)
{
	struct i915_address_space *old = ctx->vm;

	GEM_BUG_ON(old && i915_vm_is_4lvl(vm) != i915_vm_is_4lvl(old));

	ctx->vm = i915_vm_get(vm);
	context_apply_all(ctx, __apply_ppgtt, vm);

	return old;
}