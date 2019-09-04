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
struct vmcs12 {scalar_t__ vm_exit_msr_load_count; scalar_t__ vm_exit_msr_store_count; scalar_t__ vm_entry_msr_load_count; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_ADDR ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_ADDR ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_MSR_STORE_ADDR ; 
 int /*<<< orphan*/  VM_EXIT_MSR_STORE_COUNT ; 
 scalar_t__ nested_vmx_check_msr_switch (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nested_vmx_check_msr_switch_controls(struct kvm_vcpu *vcpu,
						struct vmcs12 *vmcs12)
{
	if (vmcs12->vm_exit_msr_load_count == 0 &&
	    vmcs12->vm_exit_msr_store_count == 0 &&
	    vmcs12->vm_entry_msr_load_count == 0)
		return 0; /* Fast path */
	if (nested_vmx_check_msr_switch(vcpu, VM_EXIT_MSR_LOAD_COUNT,
					VM_EXIT_MSR_LOAD_ADDR) ||
	    nested_vmx_check_msr_switch(vcpu, VM_EXIT_MSR_STORE_COUNT,
					VM_EXIT_MSR_STORE_ADDR) ||
	    nested_vmx_check_msr_switch(vcpu, VM_ENTRY_MSR_LOAD_COUNT,
					VM_ENTRY_MSR_LOAD_ADDR))
		return -EINVAL;
	return 0;
}