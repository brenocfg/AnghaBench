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
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pc; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 int ST0_ERL ; 
 int ST0_EXL ; 
 int /*<<< orphan*/  kvm_clear_c0_guest_status (struct mips_coproc*,int) ; 
 int /*<<< orphan*/  kvm_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_c0_guest_epc (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_read_c0_guest_errorepc (struct mips_coproc*) ; 
 int kvm_read_c0_guest_status (struct mips_coproc*) ; 

enum emulation_result kvm_mips_emul_eret(struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	enum emulation_result er = EMULATE_DONE;

	if (kvm_read_c0_guest_status(cop0) & ST0_ERL) {
		kvm_clear_c0_guest_status(cop0, ST0_ERL);
		vcpu->arch.pc = kvm_read_c0_guest_errorepc(cop0);
	} else if (kvm_read_c0_guest_status(cop0) & ST0_EXL) {
		kvm_debug("[%#lx] ERET to %#lx\n", vcpu->arch.pc,
			  kvm_read_c0_guest_epc(cop0));
		kvm_clear_c0_guest_status(cop0, ST0_EXL);
		vcpu->arch.pc = kvm_read_c0_guest_epc(cop0);

	} else {
		kvm_err("[%#lx] ERET when MIPS_SR_EXL|MIPS_SR_ERL == 0\n",
			vcpu->arch.pc);
		er = EMULATE_FAIL;
	}

	return er;
}