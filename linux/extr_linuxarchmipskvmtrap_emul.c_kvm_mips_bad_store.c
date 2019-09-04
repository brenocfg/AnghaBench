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
union mips_instruction {int /*<<< orphan*/  word; } ;
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_run {void* exit_reason; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int CAUSEF_BD ; 
 int EMULATE_FAIL ; 
 void* KVM_EXIT_INTERNAL_ERROR ; 
 void* KVM_EXIT_MMIO ; 
 int RESUME_HOST ; 
 int /*<<< orphan*/  kvm_err (char*) ; 
 int kvm_get_badinstr (int*,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_mips_emulate_store (union mips_instruction,int,struct kvm_run*,struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_mips_bad_store(u32 cause, u32 *opc, struct kvm_run *run,
			      struct kvm_vcpu *vcpu)
{
	enum emulation_result er;
	union mips_instruction inst;
	int err;

	/* Fetch the instruction. */
	if (cause & CAUSEF_BD)
		opc += 1;
	err = kvm_get_badinstr(opc, vcpu, &inst.word);
	if (err) {
		run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		return RESUME_HOST;
	}

	/* Emulate the store */
	er = kvm_mips_emulate_store(inst, cause, run, vcpu);
	if (er == EMULATE_FAIL) {
		kvm_err("Emulate store to MMIO space failed\n");
		run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
	} else {
		run->exit_reason = KVM_EXIT_MMIO;
	}
	return RESUME_HOST;
}