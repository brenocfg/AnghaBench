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
struct TYPE_2__ {unsigned long line_size; unsigned long ways; unsigned long sets; } ;

/* Variables and functions */
 size_t ICACHE ; 
 TYPE_1__* L1_cache_info ; 
 int /*<<< orphan*/  __nds32__isb () ; 

void cpu_icache_inval_all(void)
{
	unsigned long end, line_size;

	line_size = L1_cache_info[ICACHE].line_size;
	end =
	    line_size * L1_cache_info[ICACHE].ways * L1_cache_info[ICACHE].sets;

	do {
		end -= line_size;
		__asm__ volatile ("\n\tcctl %0, L1I_IX_INVAL"::"r" (end));
		end -= line_size;
		__asm__ volatile ("\n\tcctl %0, L1I_IX_INVAL"::"r" (end));
		end -= line_size;
		__asm__ volatile ("\n\tcctl %0, L1I_IX_INVAL"::"r" (end));
		end -= line_size;
		__asm__ volatile ("\n\tcctl %0, L1I_IX_INVAL"::"r" (end));
	} while (end > 0);
	__nds32__isb();
}