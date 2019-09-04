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
typedef  void* u32 ;
struct TYPE_4__ {void** tlbps; void** tlbcfg; void* eptcfg; void* mmucfg; TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {void* mas6; void* mas4; void* mas7_3; void* mas2; void* mas1; void* mas0; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_REG_PPC_EPTCFG 143 
#define  KVM_REG_PPC_MAS0 142 
#define  KVM_REG_PPC_MAS1 141 
#define  KVM_REG_PPC_MAS2 140 
#define  KVM_REG_PPC_MAS4 139 
#define  KVM_REG_PPC_MAS6 138 
#define  KVM_REG_PPC_MAS7_3 137 
#define  KVM_REG_PPC_MMUCFG 136 
#define  KVM_REG_PPC_TLB0CFG 135 
#define  KVM_REG_PPC_TLB0PS 134 
#define  KVM_REG_PPC_TLB1CFG 133 
#define  KVM_REG_PPC_TLB1PS 132 
#define  KVM_REG_PPC_TLB2CFG 131 
#define  KVM_REG_PPC_TLB2PS 130 
#define  KVM_REG_PPC_TLB3CFG 129 
#define  KVM_REG_PPC_TLB3PS 128 
 void* set_reg_val (int,union kvmppc_one_reg) ; 

int kvmppc_set_one_reg_e500_tlb(struct kvm_vcpu *vcpu, u64 id,
			       union kvmppc_one_reg *val)
{
	int r = 0;
	long int i;

	switch (id) {
	case KVM_REG_PPC_MAS0:
		vcpu->arch.shared->mas0 = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_MAS1:
		vcpu->arch.shared->mas1 = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_MAS2:
		vcpu->arch.shared->mas2 = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_MAS7_3:
		vcpu->arch.shared->mas7_3 = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_MAS4:
		vcpu->arch.shared->mas4 = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_MAS6:
		vcpu->arch.shared->mas6 = set_reg_val(id, *val);
		break;
	/* Only allow MMU registers to be set to the config supported by KVM */
	case KVM_REG_PPC_MMUCFG: {
		u32 reg = set_reg_val(id, *val);
		if (reg != vcpu->arch.mmucfg)
			r = -EINVAL;
		break;
	}
	case KVM_REG_PPC_EPTCFG: {
		u32 reg = set_reg_val(id, *val);
		if (reg != vcpu->arch.eptcfg)
			r = -EINVAL;
		break;
	}
	case KVM_REG_PPC_TLB0CFG:
	case KVM_REG_PPC_TLB1CFG:
	case KVM_REG_PPC_TLB2CFG:
	case KVM_REG_PPC_TLB3CFG: {
		/* MMU geometry (N_ENTRY/ASSOC) can be set only using SW_TLB */
		u32 reg = set_reg_val(id, *val);
		i = id - KVM_REG_PPC_TLB0CFG;
		if (reg != vcpu->arch.tlbcfg[i])
			r = -EINVAL;
		break;
	}
	case KVM_REG_PPC_TLB0PS:
	case KVM_REG_PPC_TLB1PS:
	case KVM_REG_PPC_TLB2PS:
	case KVM_REG_PPC_TLB3PS: {
		u32 reg = set_reg_val(id, *val);
		i = id - KVM_REG_PPC_TLB0PS;
		if (reg != vcpu->arch.tlbps[i])
			r = -EINVAL;
		break;
	}
	default:
		r = -EINVAL;
		break;
	}

	return r;
}