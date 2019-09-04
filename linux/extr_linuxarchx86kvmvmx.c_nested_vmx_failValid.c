#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  vm_instruction_error; } ;
struct TYPE_4__ {unsigned long long current_vmptr; } ;
struct TYPE_5__ {TYPE_1__ nested; } ;

/* Variables and functions */
 int X86_EFLAGS_AF ; 
 int X86_EFLAGS_CF ; 
 int X86_EFLAGS_OF ; 
 int X86_EFLAGS_PF ; 
 int X86_EFLAGS_SF ; 
 int X86_EFLAGS_ZF ; 
 TYPE_3__* get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_failInvalid (struct kvm_vcpu*) ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 
 int vmx_get_rflags (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_set_rflags (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void nested_vmx_failValid(struct kvm_vcpu *vcpu,
					u32 vm_instruction_error)
{
	if (to_vmx(vcpu)->nested.current_vmptr == -1ull) {
		/*
		 * failValid writes the error number to the current VMCS, which
		 * can't be done there isn't a current VMCS.
		 */
		nested_vmx_failInvalid(vcpu);
		return;
	}
	vmx_set_rflags(vcpu, (vmx_get_rflags(vcpu)
			& ~(X86_EFLAGS_CF | X86_EFLAGS_PF | X86_EFLAGS_AF |
			    X86_EFLAGS_SF | X86_EFLAGS_OF))
			| X86_EFLAGS_ZF);
	get_vmcs12(vcpu)->vm_instruction_error = vm_instruction_error;
	/*
	 * We don't need to force a shadow sync because
	 * VM_INSTRUCTION_ERROR is not shadowed
	 */
}