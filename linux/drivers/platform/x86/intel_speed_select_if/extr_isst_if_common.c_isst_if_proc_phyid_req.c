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
typedef  int /*<<< orphan*/  u8 ;
struct isst_if_cpu_map {size_t logical_cpu; int /*<<< orphan*/  physical_cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  punit_cpu_id; } ;

/* Variables and functions */
 long EINVAL ; 
 TYPE_1__* isst_cpu_info ; 
 size_t nr_cpu_ids ; 
 size_t num_possible_cpus () ; 

__attribute__((used)) static long isst_if_proc_phyid_req(u8 *cmd_ptr, int *write_only, int resume)
{
	struct isst_if_cpu_map *cpu_map;

	cpu_map = (struct isst_if_cpu_map *)cmd_ptr;
	if (cpu_map->logical_cpu >= nr_cpu_ids ||
	    cpu_map->logical_cpu >= num_possible_cpus())
		return -EINVAL;

	*write_only = 0;
	cpu_map->physical_cpu = isst_cpu_info[cpu_map->logical_cpu].punit_cpu_id;

	return 0;
}