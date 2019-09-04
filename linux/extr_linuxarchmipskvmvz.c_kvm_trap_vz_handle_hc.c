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
union mips_instruction {int /*<<< orphan*/  word; } ;
typedef  int u32 ;
struct TYPE_2__ {unsigned long pc; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int CAUSEF_BD ; 
 int EMULATE_FAIL ; 
 int kvm_get_badinstr (int*,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_mips_emul_hypcall (struct kvm_vcpu*,union mips_instruction) ; 
 int update_pc (struct kvm_vcpu*,int) ; 

__attribute__((used)) static enum emulation_result kvm_trap_vz_handle_hc(u32 cause, u32 *opc,
						   struct kvm_vcpu *vcpu)
{
	enum emulation_result er;
	union mips_instruction inst;
	unsigned long curr_pc;
	int err;

	if (cause & CAUSEF_BD)
		opc += 1;
	err = kvm_get_badinstr(opc, vcpu, &inst.word);
	if (err)
		return EMULATE_FAIL;

	/*
	 * Update PC and hold onto current PC in case there is
	 * an error and we want to rollback the PC
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	if (er == EMULATE_FAIL)
		return er;

	er = kvm_mips_emul_hypcall(vcpu, inst);
	if (er == EMULATE_FAIL)
		vcpu->arch.pc = curr_pc;

	return er;
}