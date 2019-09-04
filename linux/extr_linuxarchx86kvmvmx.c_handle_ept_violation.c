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
struct TYPE_3__ {unsigned long exit_qualification; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_4__ {int idt_vectoring_info; } ;

/* Variables and functions */
 unsigned long EPT_VIOLATION_ACC_INSTR ; 
 unsigned long EPT_VIOLATION_ACC_READ ; 
 unsigned long EPT_VIOLATION_ACC_WRITE ; 
 unsigned long EPT_VIOLATION_EXECUTABLE ; 
 unsigned long EPT_VIOLATION_READABLE ; 
 unsigned long EPT_VIOLATION_WRITABLE ; 
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int /*<<< orphan*/  GUEST_INTR_STATE_NMI ; 
 int /*<<< orphan*/  GUEST_PHYSICAL_ADDRESS ; 
 unsigned long INTR_INFO_UNBLOCK_NMI ; 
 int /*<<< orphan*/  PFERR_FETCH_MASK ; 
 int /*<<< orphan*/  PFERR_GUEST_FINAL_MASK ; 
 int /*<<< orphan*/  PFERR_GUEST_PAGE_MASK ; 
 int /*<<< orphan*/  PFERR_PRESENT_MASK ; 
 int /*<<< orphan*/  PFERR_USER_MASK ; 
 int /*<<< orphan*/  PFERR_WRITE_MASK ; 
 int VECTORING_INFO_VALID_MASK ; 
 scalar_t__ enable_vnmi ; 
 int kvm_mmu_page_fault (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_page_fault (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vmcs_read64 (int /*<<< orphan*/ ) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_ept_violation(struct kvm_vcpu *vcpu)
{
	unsigned long exit_qualification;
	gpa_t gpa;
	u64 error_code;

	exit_qualification = vmcs_readl(EXIT_QUALIFICATION);

	/*
	 * EPT violation happened while executing iret from NMI,
	 * "blocked by NMI" bit has to be set before next VM entry.
	 * There are errata that may cause this bit to not be set:
	 * AAK134, BY25.
	 */
	if (!(to_vmx(vcpu)->idt_vectoring_info & VECTORING_INFO_VALID_MASK) &&
			enable_vnmi &&
			(exit_qualification & INTR_INFO_UNBLOCK_NMI))
		vmcs_set_bits(GUEST_INTERRUPTIBILITY_INFO, GUEST_INTR_STATE_NMI);

	gpa = vmcs_read64(GUEST_PHYSICAL_ADDRESS);
	trace_kvm_page_fault(gpa, exit_qualification);

	/* Is it a read fault? */
	error_code = (exit_qualification & EPT_VIOLATION_ACC_READ)
		     ? PFERR_USER_MASK : 0;
	/* Is it a write fault? */
	error_code |= (exit_qualification & EPT_VIOLATION_ACC_WRITE)
		      ? PFERR_WRITE_MASK : 0;
	/* Is it a fetch fault? */
	error_code |= (exit_qualification & EPT_VIOLATION_ACC_INSTR)
		      ? PFERR_FETCH_MASK : 0;
	/* ept page table entry is present? */
	error_code |= (exit_qualification &
		       (EPT_VIOLATION_READABLE | EPT_VIOLATION_WRITABLE |
			EPT_VIOLATION_EXECUTABLE))
		      ? PFERR_PRESENT_MASK : 0;

	error_code |= (exit_qualification & 0x100) != 0 ?
	       PFERR_GUEST_FINAL_MASK : PFERR_GUEST_PAGE_MASK;

	vcpu->arch.exit_qualification = exit_qualification;
	return kvm_mmu_page_fault(vcpu, gpa, error_code, NULL, 0);
}