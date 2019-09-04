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
typedef  union kvmppc_one_reg {int dummy; } kvmppc_one_reg ;
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int hior_explicit; void* vtb; void* hior; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_REG_PPC_HIOR 131 
#define  KVM_REG_PPC_LPCR 130 
#define  KVM_REG_PPC_LPCR_64 129 
#define  KVM_REG_PPC_VTB 128 
 int /*<<< orphan*/  kvmppc_set_lpcr_pr (struct kvm_vcpu*,void*) ; 
 void* set_reg_val (int,union kvmppc_one_reg) ; 
 TYPE_1__* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvmppc_set_one_reg_pr(struct kvm_vcpu *vcpu, u64 id,
				 union kvmppc_one_reg *val)
{
	int r = 0;

	switch (id) {
	case KVM_REG_PPC_HIOR:
		to_book3s(vcpu)->hior = set_reg_val(id, *val);
		to_book3s(vcpu)->hior_explicit = true;
		break;
	case KVM_REG_PPC_VTB:
		to_book3s(vcpu)->vtb = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_LPCR:
	case KVM_REG_PPC_LPCR_64:
		kvmppc_set_lpcr_pr(vcpu, set_reg_val(id, *val));
		break;
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	case KVM_REG_PPC_TFHAR:
		vcpu->arch.tfhar = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TFIAR:
		vcpu->arch.tfiar = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TEXASR:
		vcpu->arch.texasr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_GPR0 ... KVM_REG_PPC_TM_GPR31:
		vcpu->arch.gpr_tm[id - KVM_REG_PPC_TM_GPR0] =
			set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_VSR0 ... KVM_REG_PPC_TM_VSR63:
	{
		int i, j;

		i = id - KVM_REG_PPC_TM_VSR0;
		if (i < 32)
			for (j = 0; j < TS_FPRWIDTH; j++)
				vcpu->arch.fp_tm.fpr[i][j] = val->vsxval[j];
		else
			if (cpu_has_feature(CPU_FTR_ALTIVEC))
				vcpu->arch.vr_tm.vr[i-32] = val->vval;
			else
				r = -ENXIO;
		break;
	}
	case KVM_REG_PPC_TM_CR:
		vcpu->arch.cr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_XER:
		vcpu->arch.xer_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_LR:
		vcpu->arch.lr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_CTR:
		vcpu->arch.ctr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_FPSCR:
		vcpu->arch.fp_tm.fpscr = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_AMR:
		vcpu->arch.amr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_PPR:
		vcpu->arch.ppr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_VRSAVE:
		vcpu->arch.vrsave_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_VSCR:
		if (cpu_has_feature(CPU_FTR_ALTIVEC))
			vcpu->arch.vr.vscr.u[3] = set_reg_val(id, *val);
		else
			r = -ENXIO;
		break;
	case KVM_REG_PPC_TM_DSCR:
		vcpu->arch.dscr_tm = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_TM_TAR:
		vcpu->arch.tar_tm = set_reg_val(id, *val);
		break;
#endif
	default:
		r = -EINVAL;
		break;
	}

	return r;
}