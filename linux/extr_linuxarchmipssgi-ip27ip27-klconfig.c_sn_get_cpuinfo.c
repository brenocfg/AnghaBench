#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nasid_t ;
struct TYPE_7__ {scalar_t__ virtid; } ;
struct TYPE_8__ {TYPE_1__ cpu_info; } ;
typedef  TYPE_2__ klcpu_t ;
struct TYPE_9__ {int /*<<< orphan*/ * g_nasidtable; } ;
typedef  TYPE_3__ gda_t ;
typedef  scalar_t__ cpuid_t ;
typedef  size_t cnodeid_t ;

/* Variables and functions */
 int CPUS_PER_NODE ; 
 TYPE_3__* GDA ; 
 size_t INVALID_CNODEID ; 
 int /*<<< orphan*/  INVALID_NASID ; 
 scalar_t__ MAXCPUS ; 
 size_t get_cpu_cnode (scalar_t__) ; 
 TYPE_2__* nasid_slice_to_cpuinfo (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__) ; 

klcpu_t *sn_get_cpuinfo(cpuid_t cpu)
{
	nasid_t nasid;
	int slice;
	klcpu_t *acpu;
	gda_t *gdap = GDA;
	cnodeid_t cnode;

	if (!(cpu < MAXCPUS)) {
		printk("sn_get_cpuinfo: illegal cpuid 0x%lx\n", cpu);
		return NULL;
	}

	cnode = get_cpu_cnode(cpu);
	if (cnode == INVALID_CNODEID)
		return NULL;

	if ((nasid = gdap->g_nasidtable[cnode]) == INVALID_NASID)
		return NULL;

	for (slice = 0; slice < CPUS_PER_NODE; slice++) {
		acpu = nasid_slice_to_cpuinfo(nasid, slice);
		if (acpu && acpu->cpu_info.virtid == cpu)
			return acpu;
	}
	return NULL;
}