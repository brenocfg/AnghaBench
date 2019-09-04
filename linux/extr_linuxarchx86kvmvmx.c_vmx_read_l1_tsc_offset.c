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
typedef  scalar_t__ u64 ;
struct vmcs12 {int cpu_based_vm_exec_control; scalar_t__ tsc_offset; } ;
struct TYPE_2__ {scalar_t__ tsc_offset; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int CPU_BASED_USE_TSC_OFFSETING ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 

__attribute__((used)) static u64 vmx_read_l1_tsc_offset(struct kvm_vcpu *vcpu)
{
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);

	if (is_guest_mode(vcpu) &&
	    (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETING))
		return vcpu->arch.tsc_offset - vmcs12->tsc_offset;

	return vcpu->arch.tsc_offset;
}