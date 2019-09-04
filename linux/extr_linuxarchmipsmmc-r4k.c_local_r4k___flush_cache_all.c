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
#define  CPU_BMIPS5000 138 
#define  CPU_LOONGSON2 137 
#define  CPU_LOONGSON3 136 
#define  CPU_R10000 135 
#define  CPU_R12000 134 
#define  CPU_R14000 133 
#define  CPU_R16000 132 
#define  CPU_R4000MC 131 
#define  CPU_R4000SC 130 
#define  CPU_R4400MC 129 
#define  CPU_R4400SC 128 
 int /*<<< orphan*/  __sync () ; 
 int current_cpu_type () ; 
 int get_ebase_cpunum () ; 
 int /*<<< orphan*/  r4k_blast_dcache () ; 
 int /*<<< orphan*/  r4k_blast_icache () ; 
 int /*<<< orphan*/  r4k_blast_scache () ; 
 int /*<<< orphan*/  r4k_blast_scache_node (int) ; 

__attribute__((used)) static inline void local_r4k___flush_cache_all(void * args)
{
	switch (current_cpu_type()) {
	case CPU_LOONGSON2:
	case CPU_R4000SC:
	case CPU_R4000MC:
	case CPU_R4400SC:
	case CPU_R4400MC:
	case CPU_R10000:
	case CPU_R12000:
	case CPU_R14000:
	case CPU_R16000:
		/*
		 * These caches are inclusive caches, that is, if something
		 * is not cached in the S-cache, we know it also won't be
		 * in one of the primary caches.
		 */
		r4k_blast_scache();
		break;

	case CPU_LOONGSON3:
		/* Use get_ebase_cpunum() for both NUMA=y/n */
		r4k_blast_scache_node(get_ebase_cpunum() >> 2);
		break;

	case CPU_BMIPS5000:
		r4k_blast_scache();
		__sync();
		break;

	default:
		r4k_blast_dcache();
		r4k_blast_icache();
		break;
	}
}