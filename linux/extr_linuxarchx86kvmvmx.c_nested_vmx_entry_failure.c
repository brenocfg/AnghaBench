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
typedef  int u32 ;
struct vmcs12 {int vm_exit_reason; unsigned long exit_qualification; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int sync_shadow_vmcs; } ;
struct TYPE_4__ {TYPE_1__ nested; } ;

/* Variables and functions */
 int VMX_EXIT_REASONS_FAILED_VMENTRY ; 
 scalar_t__ enable_shadow_vmcs ; 
 int /*<<< orphan*/  load_vmcs12_host_state (struct kvm_vcpu*,struct vmcs12*) ; 
 int /*<<< orphan*/  nested_vmx_succeed (struct kvm_vcpu*) ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static void nested_vmx_entry_failure(struct kvm_vcpu *vcpu,
			struct vmcs12 *vmcs12,
			u32 reason, unsigned long qualification)
{
	load_vmcs12_host_state(vcpu, vmcs12);
	vmcs12->vm_exit_reason = reason | VMX_EXIT_REASONS_FAILED_VMENTRY;
	vmcs12->exit_qualification = qualification;
	nested_vmx_succeed(vcpu);
	if (enable_shadow_vmcs)
		to_vmx(vcpu)->nested.sync_shadow_vmcs = true;
}