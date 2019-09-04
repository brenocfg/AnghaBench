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
struct cpu_cacheinfo {unsigned int num_levels; unsigned int num_leaves; } ;

/* Variables and functions */
 unsigned int CACHE_TYPE_NOCACHE ; 
 unsigned int CACHE_TYPE_SEPARATE ; 
 unsigned int MAX_CACHE_LEVEL ; 
 scalar_t__ acpi_disabled ; 
 unsigned int acpi_find_last_cache_level (unsigned int) ; 
 unsigned int get_cache_type (unsigned int) ; 
 struct cpu_cacheinfo* get_cpu_cacheinfo (unsigned int) ; 
 unsigned int of_find_last_cache_level (unsigned int) ; 

__attribute__((used)) static int __init_cache_level(unsigned int cpu)
{
	unsigned int ctype, level, leaves, fw_level;
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	for (level = 1, leaves = 0; level <= MAX_CACHE_LEVEL; level++) {
		ctype = get_cache_type(level);
		if (ctype == CACHE_TYPE_NOCACHE) {
			level--;
			break;
		}
		/* Separate instruction and data caches */
		leaves += (ctype == CACHE_TYPE_SEPARATE) ? 2 : 1;
	}

	if (acpi_disabled)
		fw_level = of_find_last_cache_level(cpu);
	else
		fw_level = acpi_find_last_cache_level(cpu);

	if (level < fw_level) {
		/*
		 * some external caches not specified in CLIDR_EL1
		 * the information may be available in the device tree
		 * only unified external caches are considered here
		 */
		leaves += (fw_level - level);
		level = fw_level;
	}

	this_cpu_ci->num_levels = level;
	this_cpu_ci->num_leaves = leaves;
	return 0;
}