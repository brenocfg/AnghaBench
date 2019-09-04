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
typedef  union kvmppc_one_reg {int dummy; } kvmppc_one_reg ;
typedef  int u64 ;
struct TYPE_3__ {int intr_msr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  vtb; int /*<<< orphan*/  hior; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVMPPC_INST_SW_BREAKPOINT ; 
#define  KVM_REG_PPC_DEBUG_INST 132 
#define  KVM_REG_PPC_HIOR 131 
#define  KVM_REG_PPC_LPCR 130 
#define  KVM_REG_PPC_LPCR_64 129 
#define  KVM_REG_PPC_VTB 128 
 int /*<<< orphan*/  LPCR_ILE ; 
 int MSR_LE ; 
 union kvmppc_one_reg get_reg_val (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvmppc_get_one_reg_pr(struct kvm_vcpu *vcpu, u64 id,
				 union kvmppc_one_reg *val)
{
	int r = 0;

	switch (id) {
	case KVM_REG_PPC_DEBUG_INST:
		*val = get_reg_val(id, KVMPPC_INST_SW_BREAKPOINT);
		break;
	case KVM_REG_PPC_HIOR:
		*val = get_reg_val(id, to_book3s(vcpu)->hior);
		break;
	case KVM_REG_PPC_VTB:
		*val = get_reg_val(id, to_book3s(vcpu)->vtb);
		break;
	case KVM_REG_PPC_LPCR:
	case KVM_REG_PPC_LPCR_64:
		/*
		 * We are only interested in the LPCR_ILE bit
		 */
		if (vcpu->arch.intr_msr & MSR_LE)
			*val = get_reg_val(id, LPCR_ILE);
		else
			*val = get_reg_val(id, 0);
		break;
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	case KVM_REG_PPC_TFHAR:
		*val = get_reg_val(id, vcpu->arch.tfhar);
		break;
	case KVM_REG_PPC_TFIAR:
		*val = get_reg_val(id, vcpu->arch.tfiar);
		break;
	case KVM_REG_PPC_TEXASR:
		*val = get_reg_val(id, vcpu->arch.texasr);
		break;
	case KVM_REG_PPC_TM_GPR0 ... KVM_REG_PPC_TM_GPR31:
		*val = get_reg_val(id,
				vcpu->arch.gpr_tm[id-KVM_REG_PPC_TM_GPR0]);
		break;
	case KVM_REG_PPC_TM_VSR0 ... KVM_REG_PPC_TM_VSR63:
	{
		int i, j;

		i = id - KVM_REG_PPC_TM_VSR0;
		if (i < 32)
			for (j = 0; j < TS_FPRWIDTH; j++)
				val->vsxval[j] = vcpu->arch.fp_tm.fpr[i][j];
		else {
			if (cpu_has_feature(CPU_FTR_ALTIVEC))
				val->vval = vcpu->arch.vr_tm.vr[i-32];
			else
				r = -ENXIO;
		}
		break;
	}
	case KVM_REG_PPC_TM_CR:
		*val = get_reg_val(id, vcpu->arch.cr_tm);
		break;
	case KVM_REG_PPC_TM_XER:
		*val = get_reg_val(id, vcpu->arch.xer_tm);
		break;
	case KVM_REG_PPC_TM_LR:
		*val = get_reg_val(id, vcpu->arch.lr_tm);
		break;
	case KVM_REG_PPC_TM_CTR:
		*val = get_reg_val(id, vcpu->arch.ctr_tm);
		break;
	case KVM_REG_PPC_TM_FPSCR:
		*val = get_reg_val(id, vcpu->arch.fp_tm.fpscr);
		break;
	case KVM_REG_PPC_TM_AMR:
		*val = get_reg_val(id, vcpu->arch.amr_tm);
		break;
	case KVM_REG_PPC_TM_PPR:
		*val = get_reg_val(id, vcpu->arch.ppr_tm);
		break;
	case KVM_REG_PPC_TM_VRSAVE:
		*val = get_reg_val(id, vcpu->arch.vrsave_tm);
		break;
	case KVM_REG_PPC_TM_VSCR:
		if (cpu_has_feature(CPU_FTR_ALTIVEC))
			*val = get_reg_val(id, vcpu->arch.vr_tm.vscr.u[3]);
		else
			r = -ENXIO;
		break;
	case KVM_REG_PPC_TM_DSCR:
		*val = get_reg_val(id, vcpu->arch.dscr_tm);
		break;
	case KVM_REG_PPC_TM_TAR:
		*val = get_reg_val(id, vcpu->arch.tar_tm);
		break;
#endif
	default:
		r = -EINVAL;
		break;
	}

	return r;
}