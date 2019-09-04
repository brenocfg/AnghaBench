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
struct cpu_cacheinfo {int num_leaves; TYPE_1__* info_list; } ;
struct TYPE_2__ {int level; int id; } ;

/* Variables and functions */
 struct cpu_cacheinfo* get_cpu_cacheinfo (int) ; 

__attribute__((used)) static int get_cache_id(int cpu, int level)
{
	struct cpu_cacheinfo *ci = get_cpu_cacheinfo(cpu);
	int i;

	for (i = 0; i < ci->num_leaves; i++) {
		if (ci->info_list[i].level == level)
			return ci->info_list[i].id;
	}

	return -1;
}