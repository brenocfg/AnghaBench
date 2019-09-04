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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int nmi_injected; void* event_exit_inst_len; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
#define  INTR_TYPE_EXT_INTR 132 
#define  INTR_TYPE_HARD_EXCEPTION 131 
#define  INTR_TYPE_NMI_INTR 130 
#define  INTR_TYPE_SOFT_EXCEPTION 129 
#define  INTR_TYPE_SOFT_INTR 128 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int VECTORING_INFO_DELIVER_CODE_MASK ; 
 int VECTORING_INFO_TYPE_MASK ; 
 int VECTORING_INFO_VALID_MASK ; 
 int VECTORING_INFO_VECTOR_MASK ; 
 int /*<<< orphan*/  kvm_clear_exception_queue (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_clear_interrupt_queue (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_queue_interrupt (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  kvm_requeue_exception (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_requeue_exception_e (struct kvm_vcpu*,int,int) ; 
 void* vmcs_read32 (int) ; 
 int /*<<< orphan*/  vmx_set_nmi_mask (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void __vmx_complete_interrupts(struct kvm_vcpu *vcpu,
				      u32 idt_vectoring_info,
				      int instr_len_field,
				      int error_code_field)
{
	u8 vector;
	int type;
	bool idtv_info_valid;

	idtv_info_valid = idt_vectoring_info & VECTORING_INFO_VALID_MASK;

	vcpu->arch.nmi_injected = false;
	kvm_clear_exception_queue(vcpu);
	kvm_clear_interrupt_queue(vcpu);

	if (!idtv_info_valid)
		return;

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	vector = idt_vectoring_info & VECTORING_INFO_VECTOR_MASK;
	type = idt_vectoring_info & VECTORING_INFO_TYPE_MASK;

	switch (type) {
	case INTR_TYPE_NMI_INTR:
		vcpu->arch.nmi_injected = true;
		/*
		 * SDM 3: 27.7.1.2 (September 2008)
		 * Clear bit "block by NMI" before VM entry if a NMI
		 * delivery faulted.
		 */
		vmx_set_nmi_mask(vcpu, false);
		break;
	case INTR_TYPE_SOFT_EXCEPTION:
		vcpu->arch.event_exit_inst_len = vmcs_read32(instr_len_field);
		/* fall through */
	case INTR_TYPE_HARD_EXCEPTION:
		if (idt_vectoring_info & VECTORING_INFO_DELIVER_CODE_MASK) {
			u32 err = vmcs_read32(error_code_field);
			kvm_requeue_exception_e(vcpu, vector, err);
		} else
			kvm_requeue_exception(vcpu, vector);
		break;
	case INTR_TYPE_SOFT_INTR:
		vcpu->arch.event_exit_inst_len = vmcs_read32(instr_len_field);
		/* fall through */
	case INTR_TYPE_EXT_INTR:
		kvm_queue_interrupt(vcpu, vector, type == INTR_TYPE_SOFT_INTR);
		break;
	default:
		break;
	}
}