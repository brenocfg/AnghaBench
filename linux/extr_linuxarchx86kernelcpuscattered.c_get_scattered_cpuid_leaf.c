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
typedef  int /*<<< orphan*/  u32 ;
struct cpuid_bit {unsigned int level; int reg; unsigned int sub_leaf; int /*<<< orphan*/  bit; scalar_t__ feature; } ;
typedef  enum cpuid_regs_idx { ____Placeholder_cpuid_regs_idx } cpuid_regs_idx ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_cpu_data ; 
 scalar_t__ cpu_has (int /*<<< orphan*/ *,scalar_t__) ; 
 struct cpuid_bit* cpuid_bits ; 

u32 get_scattered_cpuid_leaf(unsigned int level, unsigned int sub_leaf,
			     enum cpuid_regs_idx reg)
{
	const struct cpuid_bit *cb;
	u32 cpuid_val = 0;

	for (cb = cpuid_bits; cb->feature; cb++) {

		if (level > cb->level)
			continue;

		if (level < cb->level)
			break;

		if (reg == cb->reg && sub_leaf == cb->sub_leaf) {
			if (cpu_has(&boot_cpu_data, cb->feature))
				cpuid_val |= BIT(cb->bit);
		}
	}

	return cpuid_val;
}