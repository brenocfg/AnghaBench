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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_CAP_SKIP_VMENTRY_L1DFLUSH ; 
 int /*<<< orphan*/  MSR_IA32_ARCH_CAPABILITIES ; 
 scalar_t__ VMENTER_L1D_FLUSH_NEVER ; 
 scalar_t__ l1tf_vmx_mitigation ; 
 int /*<<< orphan*/  rdmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u64 kvm_get_arch_capabilities(void)
{
	u64 data;

	rdmsrl_safe(MSR_IA32_ARCH_CAPABILITIES, &data);

	/*
	 * If we're doing cache flushes (either "always" or "cond")
	 * we will do one whenever the guest does a vmlaunch/vmresume.
	 * If an outer hypervisor is doing the cache flush for us
	 * (VMENTER_L1D_FLUSH_NESTED_VM), we can safely pass that
	 * capability to the guest too, and if EPT is disabled we're not
	 * vulnerable.  Overall, only VMENTER_L1D_FLUSH_NEVER will
	 * require a nested hypervisor to do a flush of its own.
	 */
	if (l1tf_vmx_mitigation != VMENTER_L1D_FLUSH_NEVER)
		data |= ARCH_CAP_SKIP_VMENTRY_L1DFLUSH;

	return data;
}