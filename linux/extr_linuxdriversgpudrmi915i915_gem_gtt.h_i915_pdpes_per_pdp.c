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
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 unsigned int GEN8_3LVL_PDPES ; 
 unsigned int GEN8_PML4ES_PER_PML4 ; 
 scalar_t__ i915_vm_is_48bit (struct i915_address_space const*) ; 

__attribute__((used)) static inline unsigned int
i915_pdpes_per_pdp(const struct i915_address_space *vm)
{
	if (i915_vm_is_48bit(vm))
		return GEN8_PML4ES_PER_PML4;

	return GEN8_3LVL_PDPES;
}