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
struct i915_address_space {scalar_t__ scratch_order; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE_64K ; 
 scalar_t__ get_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
i915_vm_has_scratch_64K(struct i915_address_space *vm)
{
	return vm->scratch_order == get_order(I915_GTT_PAGE_SIZE_64K);
}