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
struct i915_gem_context {int /*<<< orphan*/  vm; } ;
struct i915_address_space {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 struct i915_address_space* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __assign_ppgtt (struct i915_gem_context*,struct i915_address_space*) ; 
 int /*<<< orphan*/  i915_vm_put (struct i915_address_space*) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int clone_vm(struct i915_gem_context *dst,
		    struct i915_gem_context *src)
{
	struct i915_address_space *vm;

	rcu_read_lock();
	do {
		vm = READ_ONCE(src->vm);
		if (!vm)
			break;

		if (!kref_get_unless_zero(&vm->ref))
			continue;

		/*
		 * This ppgtt may have be reallocated between
		 * the read and the kref, and reassigned to a third
		 * context. In order to avoid inadvertent sharing
		 * of this ppgtt with that third context (and not
		 * src), we have to confirm that we have the same
		 * ppgtt after passing through the strong memory
		 * barrier implied by a successful
		 * kref_get_unless_zero().
		 *
		 * Once we have acquired the current ppgtt of src,
		 * we no longer care if it is released from src, as
		 * it cannot be reallocated elsewhere.
		 */

		if (vm == READ_ONCE(src->vm))
			break;

		i915_vm_put(vm);
	} while (1);
	rcu_read_unlock();

	if (vm) {
		__assign_ppgtt(dst, vm);
		i915_vm_put(vm);
	}

	return 0;
}