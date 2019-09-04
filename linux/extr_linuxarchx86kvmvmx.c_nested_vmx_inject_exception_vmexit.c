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
typedef  unsigned int u32 ;
struct vmcs12 {int idt_vectoring_info_field; int /*<<< orphan*/  vm_exit_intr_error_code; } ;
struct TYPE_3__ {unsigned int nr; int /*<<< orphan*/  error_code; scalar_t__ has_error_code; } ;
struct TYPE_4__ {TYPE_1__ exception; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_REASON_EXCEPTION_NMI ; 
 unsigned int INTR_INFO_DELIVER_CODE_MASK ; 
 unsigned int INTR_INFO_UNBLOCK_NMI ; 
 unsigned int INTR_INFO_VALID_MASK ; 
 unsigned int INTR_TYPE_HARD_EXCEPTION ; 
 unsigned int INTR_TYPE_SOFT_EXCEPTION ; 
 int VECTORING_INFO_VALID_MASK ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ kvm_exception_is_soft (unsigned int) ; 
 int /*<<< orphan*/  nested_vmx_vmexit (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 scalar_t__ vmx_get_nmi_mask (struct kvm_vcpu*) ; 

__attribute__((used)) static void nested_vmx_inject_exception_vmexit(struct kvm_vcpu *vcpu,
					       unsigned long exit_qual)
{
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
	unsigned int nr = vcpu->arch.exception.nr;
	u32 intr_info = nr | INTR_INFO_VALID_MASK;

	if (vcpu->arch.exception.has_error_code) {
		vmcs12->vm_exit_intr_error_code = vcpu->arch.exception.error_code;
		intr_info |= INTR_INFO_DELIVER_CODE_MASK;
	}

	if (kvm_exception_is_soft(nr))
		intr_info |= INTR_TYPE_SOFT_EXCEPTION;
	else
		intr_info |= INTR_TYPE_HARD_EXCEPTION;

	if (!(vmcs12->idt_vectoring_info_field & VECTORING_INFO_VALID_MASK) &&
	    vmx_get_nmi_mask(vcpu))
		intr_info |= INTR_INFO_UNBLOCK_NMI;

	nested_vmx_vmexit(vcpu, EXIT_REASON_EXCEPTION_NMI, intr_info, exit_qual);
}