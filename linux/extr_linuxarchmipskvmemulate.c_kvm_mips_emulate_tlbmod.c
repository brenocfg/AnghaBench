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
struct kvm_vcpu_arch {unsigned long host_cp0_badvaddr; scalar_t__ pc; struct mips_coproc* cop0; } ;
struct kvm_vcpu {struct kvm_vcpu_arch arch; } ;
struct kvm_run {int dummy; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int CAUSEB_EXCCODE ; 
 int CAUSEF_BD ; 
 int EMULATE_DONE ; 
 int EXCCODE_MOD ; 
 unsigned long KVM_ENTRYHI_ASID ; 
 int ST0_EXL ; 
 unsigned long VPN2_MASK ; 
 int /*<<< orphan*/  kvm_change_c0_guest_cause (struct mips_coproc*,int,int) ; 
 int /*<<< orphan*/  kvm_clear_c0_guest_cause (struct mips_coproc*,int) ; 
 int /*<<< orphan*/  kvm_debug (char*,scalar_t__) ; 
 scalar_t__ kvm_mips_guest_exception_base (struct kvm_vcpu*) ; 
 unsigned long kvm_read_c0_guest_entryhi (struct mips_coproc*) ; 
 int kvm_read_c0_guest_status (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_set_c0_guest_cause (struct mips_coproc*,int) ; 
 int /*<<< orphan*/  kvm_set_c0_guest_status (struct mips_coproc*,int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_badvaddr (struct mips_coproc*,unsigned long) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_entryhi (struct mips_coproc*,unsigned long) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_epc (struct mips_coproc*,scalar_t__) ; 

enum emulation_result kvm_mips_emulate_tlbmod(u32 cause,
					      u32 *opc,
					      struct kvm_run *run,
					      struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	unsigned long entryhi = (vcpu->arch.host_cp0_badvaddr & VPN2_MASK) |
			(kvm_read_c0_guest_entryhi(cop0) & KVM_ENTRYHI_ASID);
	struct kvm_vcpu_arch *arch = &vcpu->arch;

	if ((kvm_read_c0_guest_status(cop0) & ST0_EXL) == 0) {
		/* save old pc */
		kvm_write_c0_guest_epc(cop0, arch->pc);
		kvm_set_c0_guest_status(cop0, ST0_EXL);

		if (cause & CAUSEF_BD)
			kvm_set_c0_guest_cause(cop0, CAUSEF_BD);
		else
			kvm_clear_c0_guest_cause(cop0, CAUSEF_BD);

		kvm_debug("[EXL == 0] Delivering TLB MOD @ pc %#lx\n",
			  arch->pc);
	} else {
		kvm_debug("[EXL == 1] Delivering TLB MOD @ pc %#lx\n",
			  arch->pc);
	}

	arch->pc = kvm_mips_guest_exception_base(vcpu) + 0x180;

	kvm_change_c0_guest_cause(cop0, (0xff),
				  (EXCCODE_MOD << CAUSEB_EXCCODE));

	/* setup badvaddr, context and entryhi registers for the guest */
	kvm_write_c0_guest_badvaddr(cop0, vcpu->arch.host_cp0_badvaddr);
	/* XXXKYMA: is the context register used by linux??? */
	kvm_write_c0_guest_entryhi(cop0, entryhi);

	return EMULATE_DONE;
}