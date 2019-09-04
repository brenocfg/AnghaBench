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
typedef  scalar_t__ u64 ;
struct linux_prom64_registers {scalar_t__ phys_addr; scalar_t__ reg_size; } ;

/* Variables and functions */

__attribute__((used)) static u64 jbusmc_dimm_group_size(u64 base,
				  const struct linux_prom64_registers *mem_regs,
				  int num_mem_regs)
{
	u64 max = base + (8UL * 1024 * 1024 * 1024);
	u64 max_seen = base;
	int i;

	for (i = 0; i < num_mem_regs; i++) {
		const struct linux_prom64_registers *ent;
		u64 this_base;
		u64 this_end;

		ent = &mem_regs[i];
		this_base = ent->phys_addr;
		this_end = this_base + ent->reg_size;
		if (base < this_base || base >= this_end)
			continue;
		if (this_end > max)
			this_end = max;
		if (this_end > max_seen)
			max_seen = this_end;
	}

	return max_seen - base;
}