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
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 scalar_t__ EMULATE_DONE ; 
 int /*<<< orphan*/  EMULTYPE_SKIP ; 
 int /*<<< orphan*/  GUEST_PHYSICAL_ADDRESS ; 
 int /*<<< orphan*/  KVM_FAST_MMIO_BUS ; 
 int /*<<< orphan*/  PFERR_RSVD_MASK ; 
 int /*<<< orphan*/  X86_FEATURE_HYPERVISOR ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ kvm_emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_io_bus_write (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kvm_mmu_page_fault (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_fast_mmio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_read64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_ept_misconfig(struct kvm_vcpu *vcpu)
{
	gpa_t gpa;

	/*
	 * A nested guest cannot optimize MMIO vmexits, because we have an
	 * nGPA here instead of the required GPA.
	 */
	gpa = vmcs_read64(GUEST_PHYSICAL_ADDRESS);
	if (!is_guest_mode(vcpu) &&
	    !kvm_io_bus_write(vcpu, KVM_FAST_MMIO_BUS, gpa, 0, NULL)) {
		trace_kvm_fast_mmio(gpa);
		/*
		 * Doing kvm_skip_emulated_instruction() depends on undefined
		 * behavior: Intel's manual doesn't mandate
		 * VM_EXIT_INSTRUCTION_LEN to be set in VMCS when EPT MISCONFIG
		 * occurs and while on real hardware it was observed to be set,
		 * other hypervisors (namely Hyper-V) don't set it, we end up
		 * advancing IP with some random value. Disable fast mmio when
		 * running nested and keep it for real hardware in hope that
		 * VM_EXIT_INSTRUCTION_LEN will always be set correctly.
		 */
		if (!static_cpu_has(X86_FEATURE_HYPERVISOR))
			return kvm_skip_emulated_instruction(vcpu);
		else
			return kvm_emulate_instruction(vcpu, EMULTYPE_SKIP) ==
								EMULATE_DONE;
	}

	return kvm_mmu_page_fault(vcpu, gpa, PFERR_RSVD_MASK, NULL, 0);
}