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
typedef  int u32 ;
struct mips_coproc {int dummy; } ;
struct kvm_vcpu_arch {scalar_t__ pc; struct mips_coproc* cop0; } ;
struct kvm_vcpu {struct kvm_vcpu_arch arch; } ;
struct kvm_run {int dummy; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int CAUSEB_EXCCODE ; 
 int CAUSEF_BD ; 
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 int EXCCODE_TR ; 
 int ST0_EXL ; 
 int /*<<< orphan*/  kvm_change_c0_guest_cause (struct mips_coproc*,int,int) ; 
 int /*<<< orphan*/  kvm_clear_c0_guest_cause (struct mips_coproc*,int) ; 
 int /*<<< orphan*/  kvm_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  kvm_err (char*) ; 
 scalar_t__ kvm_mips_guest_exception_base (struct kvm_vcpu*) ; 
 int kvm_read_c0_guest_status (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_set_c0_guest_cause (struct mips_coproc*,int) ; 
 int /*<<< orphan*/  kvm_set_c0_guest_status (struct mips_coproc*,int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_epc (struct mips_coproc*,scalar_t__) ; 

enum emulation_result kvm_mips_emulate_trap_exc(u32 cause,
						u32 *opc,
						struct kvm_run *run,
						struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	struct kvm_vcpu_arch *arch = &vcpu->arch;
	enum emulation_result er = EMULATE_DONE;

	if ((kvm_read_c0_guest_status(cop0) & ST0_EXL) == 0) {
		/* save old pc */
		kvm_write_c0_guest_epc(cop0, arch->pc);
		kvm_set_c0_guest_status(cop0, ST0_EXL);

		if (cause & CAUSEF_BD)
			kvm_set_c0_guest_cause(cop0, CAUSEF_BD);
		else
			kvm_clear_c0_guest_cause(cop0, CAUSEF_BD);

		kvm_debug("Delivering TRAP @ pc %#lx\n", arch->pc);

		kvm_change_c0_guest_cause(cop0, (0xff),
					  (EXCCODE_TR << CAUSEB_EXCCODE));

		/* Set PC to the exception entry point */
		arch->pc = kvm_mips_guest_exception_base(vcpu) + 0x180;

	} else {
		kvm_err("Trying to deliver TRAP when EXL is already set\n");
		er = EMULATE_FAIL;
	}

	return er;
}