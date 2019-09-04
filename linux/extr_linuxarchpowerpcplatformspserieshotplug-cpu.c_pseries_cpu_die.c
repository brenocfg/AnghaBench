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
struct TYPE_2__ {scalar_t__ cpu_start; } ;

/* Variables and functions */
 scalar_t__ CPU_STATE_INACTIVE ; 
 scalar_t__ CPU_STATE_OFFLINE ; 
 int QCSS_HARDWARE_ERROR ; 
 int QCSS_STOPPED ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ get_cpu_current_state (unsigned int) ; 
 unsigned int get_hard_smp_processor_id (unsigned int) ; 
 scalar_t__ get_preferred_offline_state (unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_1__** paca_ptrs ; 
 int /*<<< orphan*/  printk (char*,unsigned int,unsigned int,int) ; 
 int smp_query_cpu_stopped (unsigned int) ; 

__attribute__((used)) static void pseries_cpu_die(unsigned int cpu)
{
	int tries;
	int cpu_status = 1;
	unsigned int pcpu = get_hard_smp_processor_id(cpu);

	if (get_preferred_offline_state(cpu) == CPU_STATE_INACTIVE) {
		cpu_status = 1;
		for (tries = 0; tries < 5000; tries++) {
			if (get_cpu_current_state(cpu) == CPU_STATE_INACTIVE) {
				cpu_status = 0;
				break;
			}
			msleep(1);
		}
	} else if (get_preferred_offline_state(cpu) == CPU_STATE_OFFLINE) {

		for (tries = 0; tries < 25; tries++) {
			cpu_status = smp_query_cpu_stopped(pcpu);
			if (cpu_status == QCSS_STOPPED ||
			    cpu_status == QCSS_HARDWARE_ERROR)
				break;
			cpu_relax();
		}
	}

	if (cpu_status != 0) {
		printk("Querying DEAD? cpu %i (%i) shows %i\n",
		       cpu, pcpu, cpu_status);
	}

	/* Isolation and deallocation are definitely done by
	 * drslot_chrp_cpu.  If they were not they would be
	 * done here.  Change isolate state to Isolate and
	 * change allocation-state to Unusable.
	 */
	paca_ptrs[cpu]->cpu_start = 0;
}