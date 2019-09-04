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
struct kvmppc_host_rm_core {int dummy; } ;
struct TYPE_2__ {struct kvmppc_host_rm_core* rm_core; } ;

/* Variables and functions */
 int cpu_nr_cores () ; 
 int grab_next_hostcore (int,struct kvmppc_host_rm_core*,int,int) ; 
 TYPE_1__* kvmppc_host_rm_ops_hv ; 
 int smp_processor_id () ; 
 int threads_shift ; 

__attribute__((used)) static inline int find_available_hostcore(int action)
{
	int core;
	int my_core = smp_processor_id() >> threads_shift;
	struct kvmppc_host_rm_core *rm_core = kvmppc_host_rm_ops_hv->rm_core;

	core = grab_next_hostcore(my_core, rm_core, cpu_nr_cores(), action);
	if (core == -1)
		core = grab_next_hostcore(core, rm_core, my_core, action);

	return core;
}