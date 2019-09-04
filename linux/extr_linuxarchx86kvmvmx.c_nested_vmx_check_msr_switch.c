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
typedef  int u64 ;
struct vmx_msr_entry {int dummy; } ;
struct vmcs12 {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pr_debug_ratelimited (char*,unsigned long,int,int,int) ; 
 scalar_t__ vmcs12_read_any (struct vmcs12*,unsigned long,int*) ; 

__attribute__((used)) static int nested_vmx_check_msr_switch(struct kvm_vcpu *vcpu,
				       unsigned long count_field,
				       unsigned long addr_field)
{
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
	int maxphyaddr;
	u64 count, addr;

	if (vmcs12_read_any(vmcs12, count_field, &count) ||
	    vmcs12_read_any(vmcs12, addr_field, &addr)) {
		WARN_ON(1);
		return -EINVAL;
	}
	if (count == 0)
		return 0;
	maxphyaddr = cpuid_maxphyaddr(vcpu);
	if (!IS_ALIGNED(addr, 16) || addr >> maxphyaddr ||
	    (addr + count * sizeof(struct vmx_msr_entry) - 1) >> maxphyaddr) {
		pr_debug_ratelimited(
			"nVMX: invalid MSR switch (0x%lx, %d, %llu, 0x%08llx)",
			addr_field, maxphyaddr, count, addr);
		return -EINVAL;
	}
	return 0;
}