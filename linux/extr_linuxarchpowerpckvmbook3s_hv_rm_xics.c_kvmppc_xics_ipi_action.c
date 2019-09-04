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
struct TYPE_3__ {scalar_t__ rm_action; } ;
struct kvmppc_host_rm_core {TYPE_1__ rm_state; int /*<<< orphan*/ * rm_data; } ;
struct TYPE_4__ {struct kvmppc_host_rm_core* rm_core; } ;

/* Variables and functions */
 TYPE_2__* kvmppc_host_rm_ops_hv ; 
 int /*<<< orphan*/  rm_host_ipi_action (scalar_t__,int /*<<< orphan*/ *) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 unsigned int threads_shift ; 

void kvmppc_xics_ipi_action(void)
{
	int core;
	unsigned int cpu = smp_processor_id();
	struct kvmppc_host_rm_core *rm_corep;

	core = cpu >> threads_shift;
	rm_corep = &kvmppc_host_rm_ops_hv->rm_core[core];

	if (rm_corep->rm_data) {
		rm_host_ipi_action(rm_corep->rm_state.rm_action,
							rm_corep->rm_data);
		/* Order these stores against the real mode KVM */
		rm_corep->rm_data = NULL;
		smp_wmb();
		rm_corep->rm_state.rm_action = 0;
	}
}