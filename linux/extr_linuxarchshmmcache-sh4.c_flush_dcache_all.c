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
struct TYPE_3__ {unsigned long sets; unsigned long entry_shift; unsigned long ways; } ;
struct TYPE_4__ {TYPE_1__ dcache; } ;

/* Variables and functions */
 unsigned long CACHE_OC_ADDRESS_ARRAY ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_2__ current_cpu_data ; 

__attribute__((used)) static void flush_dcache_all(void)
{
	unsigned long addr, end_addr, entry_offset;

	end_addr = CACHE_OC_ADDRESS_ARRAY +
		(current_cpu_data.dcache.sets <<
		 current_cpu_data.dcache.entry_shift) *
			current_cpu_data.dcache.ways;

	entry_offset = 1 << current_cpu_data.dcache.entry_shift;

	for (addr = CACHE_OC_ADDRESS_ARRAY; addr < end_addr; ) {
		__raw_writel(0, addr); addr += entry_offset;
		__raw_writel(0, addr); addr += entry_offset;
		__raw_writel(0, addr); addr += entry_offset;
		__raw_writel(0, addr); addr += entry_offset;
		__raw_writel(0, addr); addr += entry_offset;
		__raw_writel(0, addr); addr += entry_offset;
		__raw_writel(0, addr); addr += entry_offset;
		__raw_writel(0, addr); addr += entry_offset;
	}
}