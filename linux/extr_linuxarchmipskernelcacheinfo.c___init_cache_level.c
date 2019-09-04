#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ waysize; } ;
struct TYPE_6__ {scalar_t__ waysize; } ;
struct TYPE_5__ {scalar_t__ waysize; } ;
struct TYPE_8__ {scalar_t__ waysize; } ;
struct cpuinfo_mips {TYPE_3__ tcache; TYPE_2__ scache; TYPE_1__ icache; TYPE_4__ dcache; } ;
struct cpu_cacheinfo {int num_levels; int num_leaves; } ;

/* Variables and functions */
 int ENOENT ; 
 struct cpuinfo_mips current_cpu_data ; 
 struct cpu_cacheinfo* get_cpu_cacheinfo (unsigned int) ; 

__attribute__((used)) static int __init_cache_level(unsigned int cpu)
{
	struct cpuinfo_mips *c = &current_cpu_data;
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	int levels = 0, leaves = 0;

	/*
	 * If Dcache is not set, we assume the cache structures
	 * are not properly initialized.
	 */
	if (c->dcache.waysize)
		levels += 1;
	else
		return -ENOENT;


	leaves += (c->icache.waysize) ? 2 : 1;

	if (c->scache.waysize) {
		levels++;
		leaves++;
	}

	if (c->tcache.waysize) {
		levels++;
		leaves++;
	}

	this_cpu_ci->num_levels = levels;
	this_cpu_ci->num_leaves = leaves;
	return 0;
}