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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int host_apf_reason; } ;
struct TYPE_4__ {int l1tf_flush_l1d; TYPE_1__ apf; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
#define  KVM_PV_REASON_PAGE_NOT_PRESENT 129 
#define  KVM_PV_REASON_PAGE_READY 128 
 int /*<<< orphan*/  kvm_async_pf_task_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_async_pf_task_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_event_needs_reinjection (struct kvm_vcpu*) ; 
 int kvm_mmu_page_fault (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kvm_mmu_unprotect_page_virt (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  trace_kvm_page_fault (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kvm_handle_page_fault(struct kvm_vcpu *vcpu, u64 error_code,
				u64 fault_address, char *insn, int insn_len)
{
	int r = 1;

	vcpu->arch.l1tf_flush_l1d = true;
	switch (vcpu->arch.apf.host_apf_reason) {
	default:
		trace_kvm_page_fault(fault_address, error_code);

		if (kvm_event_needs_reinjection(vcpu))
			kvm_mmu_unprotect_page_virt(vcpu, fault_address);
		r = kvm_mmu_page_fault(vcpu, fault_address, error_code, insn,
				insn_len);
		break;
	case KVM_PV_REASON_PAGE_NOT_PRESENT:
		vcpu->arch.apf.host_apf_reason = 0;
		local_irq_disable();
		kvm_async_pf_task_wait(fault_address, 0);
		local_irq_enable();
		break;
	case KVM_PV_REASON_PAGE_READY:
		vcpu->arch.apf.host_apf_reason = 0;
		local_irq_disable();
		kvm_async_pf_task_wake(fault_address);
		local_irq_enable();
		break;
	}
	return r;
}