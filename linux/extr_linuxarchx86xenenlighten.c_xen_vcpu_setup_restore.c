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
 scalar_t__ cpu_online (int) ; 
 scalar_t__ xen_hvm_domain () ; 
 scalar_t__ xen_pv_domain () ; 
 int /*<<< orphan*/  xen_vcpu_info_reset (int) ; 
 int xen_vcpu_setup (int) ; 

__attribute__((used)) static int xen_vcpu_setup_restore(int cpu)
{
	int rc = 0;

	/* Any per_cpu(xen_vcpu) is stale, so reset it */
	xen_vcpu_info_reset(cpu);

	/*
	 * For PVH and PVHVM, setup online VCPUs only. The rest will
	 * be handled by hotplug.
	 */
	if (xen_pv_domain() ||
	    (xen_hvm_domain() && cpu_online(cpu))) {
		rc = xen_vcpu_setup(cpu);
	}

	return rc;
}