#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long line_size; } ;

/* Variables and functions */
 size_t DCACHE ; 
 TYPE_1__* L1_cache_info ; 
 int /*<<< orphan*/  cpu_cache_wbinval_range (unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void flush_icache_range(unsigned long start, unsigned long end)
{
	unsigned long line_size, flags;
	line_size = L1_cache_info[DCACHE].line_size;
	start = start & ~(line_size - 1);
	end = (end + line_size - 1) & ~(line_size - 1);
	local_irq_save(flags);
	cpu_cache_wbinval_range(start, end, 1);
	local_irq_restore(flags);
}