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
struct TYPE_4__ {TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_run {int dummy; } ;
struct TYPE_3__ {unsigned int msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMULATED_MFMSR_EXITS ; 
 int /*<<< orphan*/  EMULATED_MTMSR_EXITS ; 
 int /*<<< orphan*/  EMULATED_RFCI_EXITS ; 
 int /*<<< orphan*/  EMULATED_RFDI_EXITS ; 
 int /*<<< orphan*/  EMULATED_RFI_EXITS ; 
 int /*<<< orphan*/  EMULATED_WRTEE_EXITS ; 
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 unsigned int MSR_EE ; 
#define  OP_19_XOP_RFCI 134 
#define  OP_19_XOP_RFDI 133 
#define  OP_19_XOP_RFI 132 
#define  OP_31_XOP_MFMSR 131 
#define  OP_31_XOP_MTMSR 130 
#define  OP_31_XOP_WRTEE 129 
#define  OP_31_XOP_WRTEEI 128 
 int get_op (unsigned int) ; 
 int get_rs (unsigned int) ; 
 int get_rt (unsigned int) ; 
 int /*<<< orphan*/  get_xop (unsigned int) ; 
 int /*<<< orphan*/  kvmppc_emul_rfci (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_emul_rfdi (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_emul_rfi (struct kvm_vcpu*) ; 
 unsigned int kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_set_exit_type (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,unsigned int) ; 

int kvmppc_booke_emulate_op(struct kvm_run *run, struct kvm_vcpu *vcpu,
                            unsigned int inst, int *advance)
{
	int emulated = EMULATE_DONE;
	int rs = get_rs(inst);
	int rt = get_rt(inst);

	switch (get_op(inst)) {
	case 19:
		switch (get_xop(inst)) {
		case OP_19_XOP_RFI:
			kvmppc_emul_rfi(vcpu);
			kvmppc_set_exit_type(vcpu, EMULATED_RFI_EXITS);
			*advance = 0;
			break;

		case OP_19_XOP_RFCI:
			kvmppc_emul_rfci(vcpu);
			kvmppc_set_exit_type(vcpu, EMULATED_RFCI_EXITS);
			*advance = 0;
			break;

		case OP_19_XOP_RFDI:
			kvmppc_emul_rfdi(vcpu);
			kvmppc_set_exit_type(vcpu, EMULATED_RFDI_EXITS);
			*advance = 0;
			break;

		default:
			emulated = EMULATE_FAIL;
			break;
		}
		break;

	case 31:
		switch (get_xop(inst)) {

		case OP_31_XOP_MFMSR:
			kvmppc_set_gpr(vcpu, rt, vcpu->arch.shared->msr);
			kvmppc_set_exit_type(vcpu, EMULATED_MFMSR_EXITS);
			break;

		case OP_31_XOP_MTMSR:
			kvmppc_set_exit_type(vcpu, EMULATED_MTMSR_EXITS);
			kvmppc_set_msr(vcpu, kvmppc_get_gpr(vcpu, rs));
			break;

		case OP_31_XOP_WRTEE:
			vcpu->arch.shared->msr = (vcpu->arch.shared->msr & ~MSR_EE)
					| (kvmppc_get_gpr(vcpu, rs) & MSR_EE);
			kvmppc_set_exit_type(vcpu, EMULATED_WRTEE_EXITS);
			break;

		case OP_31_XOP_WRTEEI:
			vcpu->arch.shared->msr = (vcpu->arch.shared->msr & ~MSR_EE)
							 | (inst & MSR_EE);
			kvmppc_set_exit_type(vcpu, EMULATED_WRTEE_EXITS);
			break;

		default:
			emulated = EMULATE_FAIL;
		}

		break;

	default:
		emulated = EMULATE_FAIL;
	}

	return emulated;
}