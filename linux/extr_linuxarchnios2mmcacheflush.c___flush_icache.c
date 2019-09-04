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
struct TYPE_2__ {int icache_line_size; unsigned long icache_size; } ;

/* Variables and functions */
 TYPE_1__ cpuinfo ; 

__attribute__((used)) static void __flush_icache(unsigned long start, unsigned long end)
{
	unsigned long addr;

	start &= ~(cpuinfo.icache_line_size - 1);
	end += (cpuinfo.icache_line_size - 1);
	end &= ~(cpuinfo.icache_line_size - 1);

	if (end > start + cpuinfo.icache_size)
		end = start + cpuinfo.icache_size;

	for (addr = start; addr < end; addr += cpuinfo.icache_line_size) {
		__asm__ __volatile__ ("   flushi %0\n"
					: /* Outputs */
					: /* Inputs  */ "r"(addr)
					/* : No clobber */);
	}
	__asm__ __volatile(" flushp\n");
}