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
struct i915_address_space {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_ppgtt_unpin_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vm_put (struct i915_address_space*) ; 
 int /*<<< orphan*/  i915_vm_to_ppgtt (struct i915_address_space*) ; 

__attribute__((used)) static void set_ppgtt_barrier(void *data)
{
	struct i915_address_space *old = data;

	if (INTEL_GEN(old->i915) < 8)
		gen6_ppgtt_unpin_all(i915_vm_to_ppgtt(old));

	i915_vm_put(old);
}