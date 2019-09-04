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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long host_cp0_badvaddr; unsigned long pc; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_run {int dummy; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int EMULATE_EXCEPT ; 
 int EMULATE_FAIL ; 
#define  KVM_MIPS_GPA 131 
#define  KVM_MIPS_GVA 130 
#define  KVM_MIPS_TLB 129 
#define  KVM_MIPS_TLBINV 128 
 int /*<<< orphan*/  kvm_mips_emulate_tlbinv_ld (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct kvm_run*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_emulate_tlbmiss_ld (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct kvm_run*,struct kvm_vcpu*) ; 
 int kvm_trap_emul_gva_fault (struct kvm_vcpu*,unsigned long,int) ; 
 int /*<<< orphan*/  kvm_trap_emul_gva_lockless_begin (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_trap_emul_gva_lockless_end (struct kvm_vcpu*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static enum emulation_result kvm_mips_guest_cache_op(int (*fn)(unsigned long),
						     unsigned long curr_pc,
						     unsigned long addr,
						     struct kvm_run *run,
						     struct kvm_vcpu *vcpu,
						     u32 cause)
{
	int err;

	for (;;) {
		/* Carefully attempt the cache operation */
		kvm_trap_emul_gva_lockless_begin(vcpu);
		err = fn(addr);
		kvm_trap_emul_gva_lockless_end(vcpu);

		if (likely(!err))
			return EMULATE_DONE;

		/*
		 * Try to handle the fault and retry, maybe we just raced with a
		 * GVA invalidation.
		 */
		switch (kvm_trap_emul_gva_fault(vcpu, addr, false)) {
		case KVM_MIPS_GVA:
		case KVM_MIPS_GPA:
			/* bad virtual or physical address */
			return EMULATE_FAIL;
		case KVM_MIPS_TLB:
			/* no matching guest TLB */
			vcpu->arch.host_cp0_badvaddr = addr;
			vcpu->arch.pc = curr_pc;
			kvm_mips_emulate_tlbmiss_ld(cause, NULL, run, vcpu);
			return EMULATE_EXCEPT;
		case KVM_MIPS_TLBINV:
			/* invalid matching guest TLB */
			vcpu->arch.host_cp0_badvaddr = addr;
			vcpu->arch.pc = curr_pc;
			kvm_mips_emulate_tlbinv_ld(cause, NULL, run, vcpu);
			return EMULATE_EXCEPT;
		default:
			break;
		};
	}
}