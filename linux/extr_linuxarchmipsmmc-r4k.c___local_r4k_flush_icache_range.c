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

/* Variables and functions */
#define  CPU_LOONGSON2 128 
 int /*<<< orphan*/  R4600_HIT_CACHEOP_WAR_IMPL ; 
 unsigned int R4K_INDEX ; 
 int /*<<< orphan*/  blast_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  blast_icache_range (unsigned long,unsigned long) ; 
 int boot_cpu_type () ; 
 int /*<<< orphan*/  cpu_has_ic_fills_f_dc ; 
 unsigned long dcache_size ; 
 unsigned long icache_size ; 
 int /*<<< orphan*/  protected_blast_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  protected_blast_icache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  protected_loongson2_blast_icache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  r4k_blast_dcache () ; 
 int /*<<< orphan*/  r4k_blast_icache () ; 

__attribute__((used)) static inline void __local_r4k_flush_icache_range(unsigned long start,
						  unsigned long end,
						  unsigned int type,
						  bool user)
{
	if (!cpu_has_ic_fills_f_dc) {
		if (type == R4K_INDEX ||
		    (type & R4K_INDEX && end - start >= dcache_size)) {
			r4k_blast_dcache();
		} else {
			R4600_HIT_CACHEOP_WAR_IMPL;
			if (user)
				protected_blast_dcache_range(start, end);
			else
				blast_dcache_range(start, end);
		}
	}

	if (type == R4K_INDEX ||
	    (type & R4K_INDEX && end - start > icache_size))
		r4k_blast_icache();
	else {
		switch (boot_cpu_type()) {
		case CPU_LOONGSON2:
			protected_loongson2_blast_icache_range(start, end);
			break;

		default:
			if (user)
				protected_blast_icache_range(start, end);
			else
				blast_icache_range(start, end);
			break;
		}
	}
}