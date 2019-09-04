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
struct TYPE_4__ {int /*<<< orphan*/ * tlbps; int /*<<< orphan*/ * tlbcfg; int /*<<< orphan*/  eptcfg; int /*<<< orphan*/  mmucfg; TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  mas6; int /*<<< orphan*/  mas4; int /*<<< orphan*/  mas7_3; int /*<<< orphan*/  mas2; int /*<<< orphan*/  mas1; int /*<<< orphan*/  mas0; } ;

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
 union kvmppc_one_reg get_reg_val (int,int /*<<< orphan*/ ) ; 

int kvmppc_get_one_reg_e500_tlb(struct kvm_vcpu *vcpu, u64 id,
				union kvmppc_one_reg *val)
{
	int r = 0;
	long int i;

	switch (id) {
	case KVM_REG_PPC_MAS0:
		*val = get_reg_val(id, vcpu->arch.shared->mas0);
		break;
	case KVM_REG_PPC_MAS1:
		*val = get_reg_val(id, vcpu->arch.shared->mas1);
		break;
	case KVM_REG_PPC_MAS2:
		*val = get_reg_val(id, vcpu->arch.shared->mas2);
		break;
	case KVM_REG_PPC_MAS7_3:
		*val = get_reg_val(id, vcpu->arch.shared->mas7_3);
		break;
	case KVM_REG_PPC_MAS4:
		*val = get_reg_val(id, vcpu->arch.shared->mas4);
		break;
	case KVM_REG_PPC_MAS6:
		*val = get_reg_val(id, vcpu->arch.shared->mas6);
		break;
	case KVM_REG_PPC_MMUCFG:
		*val = get_reg_val(id, vcpu->arch.mmucfg);
		break;
	case KVM_REG_PPC_EPTCFG:
		*val = get_reg_val(id, vcpu->arch.eptcfg);
		break;
	case KVM_REG_PPC_TLB0CFG:
	case KVM_REG_PPC_TLB1CFG:
	case KVM_REG_PPC_TLB2CFG:
	case KVM_REG_PPC_TLB3CFG:
		i = id - KVM_REG_PPC_TLB0CFG;
		*val = get_reg_val(id, vcpu->arch.tlbcfg[i]);
		break;
	case KVM_REG_PPC_TLB0PS:
	case KVM_REG_PPC_TLB1PS:
	case KVM_REG_PPC_TLB2PS:
	case KVM_REG_PPC_TLB3PS:
		i = id - KVM_REG_PPC_TLB0PS;
		*val = get_reg_val(id, vcpu->arch.tlbps[i]);
		break;
	default:
		r = -EINVAL;
		break;
	}

	return r;
}