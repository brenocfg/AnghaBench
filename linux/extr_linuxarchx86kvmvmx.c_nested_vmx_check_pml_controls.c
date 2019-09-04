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
struct vmcs12 {int pml_address; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 int /*<<< orphan*/  SECONDARY_EXEC_ENABLE_PML ; 
 int cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 scalar_t__ nested_cpu_has2 (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_ept (struct vmcs12*) ; 

__attribute__((used)) static int nested_vmx_check_pml_controls(struct kvm_vcpu *vcpu,
					 struct vmcs12 *vmcs12)
{
	u64 address = vmcs12->pml_address;
	int maxphyaddr = cpuid_maxphyaddr(vcpu);

	if (nested_cpu_has2(vmcs12, SECONDARY_EXEC_ENABLE_PML)) {
		if (!nested_cpu_has_ept(vmcs12) ||
		    !IS_ALIGNED(address, 4096)  ||
		    address >> maxphyaddr)
			return -EINVAL;
	}

	return 0;
}