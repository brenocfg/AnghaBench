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
struct i915_address_space {unsigned long long total; int /*<<< orphan*/  top; } ;

/* Variables and functions */
 unsigned int __gen8_pte_shift (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int gen8_pd_top_count(const struct i915_address_space *vm)
{
	unsigned int shift = __gen8_pte_shift(vm->top);
	return (vm->total + (1ull << shift) - 1) >> shift;
}