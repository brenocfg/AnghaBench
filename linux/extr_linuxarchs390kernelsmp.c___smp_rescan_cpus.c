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
typedef  int u16 ;
struct sclp_core_info {int combined; int configured; TYPE_1__* core; } ;
struct pcpu {int address; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_4__ {scalar_t__ has_core_type; } ;
struct TYPE_3__ {scalar_t__ type; int core_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_STATE_CONFIGURED ; 
 int /*<<< orphan*/  CPU_STATE_STANDBY ; 
 int /*<<< orphan*/  POLARIZATION_UNKNOWN ; 
 scalar_t__ boot_core_type ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpu_present_mask ; 
 int cpumask_first (int /*<<< orphan*/ *) ; 
 int cpumask_next (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 struct pcpu* pcpu_devices ; 
 scalar_t__ pcpu_find_address (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ sclp ; 
 int /*<<< orphan*/  set_cpu_present (int,int) ; 
 scalar_t__ smp_add_present_cpu (int) ; 
 int smp_cpu_mt_shift ; 
 int smp_cpu_mtid ; 
 int /*<<< orphan*/  smp_cpu_set_polarization (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __smp_rescan_cpus(struct sclp_core_info *info, int sysfs_add)
{
	struct pcpu *pcpu;
	cpumask_t avail;
	int cpu, nr, i, j;
	u16 address;

	nr = 0;
	cpumask_xor(&avail, cpu_possible_mask, cpu_present_mask);
	cpu = cpumask_first(&avail);
	for (i = 0; (i < info->combined) && (cpu < nr_cpu_ids); i++) {
		if (sclp.has_core_type && info->core[i].type != boot_core_type)
			continue;
		address = info->core[i].core_id << smp_cpu_mt_shift;
		for (j = 0; j <= smp_cpu_mtid; j++) {
			if (pcpu_find_address(cpu_present_mask, address + j))
				continue;
			pcpu = pcpu_devices + cpu;
			pcpu->address = address + j;
			pcpu->state =
				(cpu >= info->configured*(smp_cpu_mtid + 1)) ?
				CPU_STATE_STANDBY : CPU_STATE_CONFIGURED;
			smp_cpu_set_polarization(cpu, POLARIZATION_UNKNOWN);
			set_cpu_present(cpu, true);
			if (sysfs_add && smp_add_present_cpu(cpu) != 0)
				set_cpu_present(cpu, false);
			else
				nr++;
			cpu = cpumask_next(cpu, &avail);
			if (cpu >= nr_cpu_ids)
				break;
		}
	}
	return nr;
}